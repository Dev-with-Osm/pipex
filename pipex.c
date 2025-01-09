#include "pipex.h"

void error_check(char *errType, char *errMsg)
{
	fprintf(stderr, "%s %s\n", errType, errMsg);
	exit(EXIT_FAILURE);
}

void err_return(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void ft_putstr(char *s, int fd)
{
	if (!s)
		return;
	write(fd, s, strlen(s));
}

void print_error(char *text, char *type, char *cmd)
{
	ft_putstr(type, 2);
	ft_putstr(": ", 2);
	ft_putstr(text, 2);
	if (cmd)
		ft_putstr(cmd, 2);
	ft_putstr("\n", 2);
}

int open_file(char *filePath, int flag)
{
	int fd;

	if (flag == 1)
		fd = open(filePath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (flag == 2)
		fd = open(filePath, O_RDONLY);
	else
		fd = open(filePath, O_RDWR | O_CREAT, 0644);

	if (fd < 0)
		error_check("Error", "Failed to open file");
	return fd;
}

char *check_cmd(char *cmd, char **env)
{
	int i = 0;

	while (env[i] && strncmp("PATH=", env[i], 5) != 0)
		i++;
	if (!env[i])
		return (print_error("command not found: ", "command failed", cmd), NULL);
	char **paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (error_check("Error", "Failed to allocate memory"), NULL);
	char *full_cmd = NULL;
	i = 0;
	while (paths[i])
	{
		char *path_with_slash = ft_strjoin(paths[i], "/");
		full_cmd = ft_strjoin(path_with_slash, cmd);
		if (access(full_cmd, X_OK) == 0)
			return full_cmd;
		i++;
	}
	print_error("command not found: ", "command failed", cmd);
	return NULL;
}

void execute_cmd(char *cmd_with_args, char **env, int input_fd, int output_fd)
{
	char **args = ft_split(cmd_with_args, ' ');
	if (!args)
		error_check("Error", "Failed to allocate memory for command arguments");
	char *cmd = check_cmd(args[0], env);
	if (!cmd)
		exit(127);
	if (dup2(input_fd, STDIN_FILENO) == -1 || dup2(output_fd, STDOUT_FILENO) == -1)
		error_check("Error", "Failed to duplicate file descriptor");
	execve(cmd, args, env);
	perror("execve");
	exit(127);
}

int main(int argc, char const *argv[], char *env[])
{
	if (argc != 5)
		error_check("Usage", "./pipex infile \"cmd1\" \"cmd2\" outfile");

	int fd[2];
	if (pipe(fd) == -1)
		err_return();

	pid_t pid1 = fork();
	if (pid1 == -1)
		err_return();

	if (pid1 == 0)

		close(fd[0]);
	int input_fd = open_file((char *)argv[1], 2);
	execute_cmd((char *)argv[2], env, input_fd, fd[1]);
}

pid_t pid2 = fork();
if (pid2 == -1)
	err_return();

if (pid2 == 0)
{

	close(fd[1]);
	int output_fd = open_file((char *)argv[4], 1);
	execute_cmd((char *)argv[3], env, fd[0], output_fd);
}

close(fd[0]);
close(fd[1]);
waitpid(pid1, NULL, 0);
waitpid(pid2, NULL, 0);

return 0;
}
