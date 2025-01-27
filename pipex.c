/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:07:58 by okhourss          #+#    #+#             */
/*   Updated: 2025/01/27 09:33:08 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cleanup_and_exit(char *error_msg, int exit_code)
{
	if (error_msg)
	{
		write(STDERR_FILENO, "pipex: ", 7);
		write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
		write(STDERR_FILENO, "\n", 1);
	}
	exit(exit_code);
}

void	child_process(int *fd, const char *infile, const char *cmd, char **env)
{
	int	file;

	close(fd[0]);
	file = open(infile, O_RDONLY);
	if (file < 0)
	{
		perror("Input file error");
		exit(EXIT_FAILURE);
	}
	if (dup2(file, STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
	{
		close(file);
		close(fd[1]);
		cleanup_and_exit("dup2 failed", EXIT_FAILURE);
	}
	close(file);
	close(fd[1]);
	execute_cmd((char *)cmd, env);
	cleanup_and_exit("command execution failed", EXIT_FAILURE);
}

void	second_child_process(int *fd, const char *outfile, const char *cmd,
		char **env)
{
	int	file;

	close(fd[1]);
	file = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
	{
		close(fd[0]);
		perror("Output file error");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(file, STDOUT_FILENO) < 0)
	{
		close(file);
		close(fd[0]);
		cleanup_and_exit("dup2 failed", EXIT_FAILURE);
	}
	close(file);
	close(fd[0]);
	execute_cmd((char *)cmd, env);
	cleanup_and_exit("command execution failed", EXIT_FAILURE);
}

void	execute_cmd(char *cmd, char **env)
{
	char	**argv_content;
	char	*cmd_path;

	if (!cmd || !env)
		cleanup_and_exit("Invalid command or environment", EXIT_FAILURE);
	argv_content = ft_split(cmd, ' ');
	if (!argv_content || !argv_content[0])
	{
		free_split(argv_content);
		cleanup_and_exit("Empty command", EXIT_FAILURE);
	}
	cmd_path = get_command_path(argv_content[0], env);
	if (!cmd_path)
	{
		free_split(argv_content);
		cleanup_and_exit("command not found", EXIT_FAILURE);
	}
	execve(cmd_path, argv_content, env);
	free(cmd_path);
	free_split(argv_content);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	main(int argc, const char *argv[], char *env[])
{
	int		fd[2];
	pid_t	pid;
	pid_t	pid_2;

	if (argc != 5)
		cleanup_and_exit("Arguments not enough!",
			EXIT_FAILURE);
	if (pipe(fd) == -1)
		cleanup_and_exit("Pipe creation failed", EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		cleanup_and_exit("Fork failed", EXIT_FAILURE);
	if (pid == 0)
		child_process(fd, argv[1], argv[2], env);
	pid_2 = fork();
	if (pid_2 < 0)
		cleanup_and_exit("Fork failed", EXIT_FAILURE);
	if (pid_2 == 0)
		second_child_process(fd, argv[4], argv[3], env);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid_2, NULL, 0);
	return (0);
}
