#include "pipex.h"

char *check_cmd(char *cmd, char **env)
{
	int i = 0;
	while (env[i] != NULL)
	{
		if (strncmp("PATH=", env[i], 5) == 0)
			break;
		i++;
	}
	if (env[i] == NULL)
	{
		printf("fghjk");
		exit(1);
	}
	char **res = ft_split(env[i], '=');
	char **split_res = ft_split(res[1], ':');
	i = 0;
	while (split_res[i])
	{
		char *str = ft_strjoin(split_res[i], "/");
		char *full_cmd = ft_strjoin(str, cmd);
		if (access(full_cmd, X_OK | F_OK) == 0)
			return (full_cmd);
		i++;
	}
	return NULL;
}

int main(int argc, char const *argv[], char *env[])
{

	if (argc != 5)
	{
		printf("Error: Too few arguments\n");
		exit(1);
	}
	int fd[2];
	if (pipe(fd) == -1)
	{
		perror("err:");
		exit(1);
	}

	pid_t pid1 = fork();
	pid_t pid2;
	if (pid1 == -1)
	{
		perror("err:");
		exit(1);
	}
	if (pid1 == 0)
	{
		// the first child process to handle the first cmd
		close(fd[0]);
		int file = open(argv[1], O_RDWR);
		dup2(file, STDIN_FILENO);
		close(file);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);

		char **args = ft_split(argv[2], ' ');
		char *cmd = check_cmd(args[0], env);
		execve(cmd, args, env);
	}

	pid2 = fork();
	if (pid2 == -1)
	{
		perror("err:");
		exit(1);
	}
	if (pid2 == 0)
	{
		waitpid(pid1, NULL, 0);
		close(fd[1]);

		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		int file = open(argv[4], O_WRONLY | O_TRUNC);
		dup2(file, 1);

		char **args = ft_split(argv[3], ' ');
		char *cmd = check_cmd(args[0], env);
		execve(cmd, args, env);
	}

	wait(NULL);

	return 0;
}