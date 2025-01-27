/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:07:52 by okhourss          #+#    #+#             */
/*   Updated: 2025/01/18 21:07:52 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*find_path_env(char **env)
{
	int		i;
	char	**env_col;
	char	*returned_str;

	i = 0;
	while (env[i])
	{
		env_col = ft_split(env[i], '=');
		if (!env_col)
			return (NULL);
		if (env_col[0] && ft_strcmp(env_col[0], "PATH") == 0)
		{
			returned_str = ft_strdup(env_col[1]);
			free_split(env_col);
			return (returned_str);
		}
		free_split(env_col);
		i++;
	}
	return (NULL);
}

char	*try_path(char **path_dirs, char *cmd)
{
	char	*new_cmd;
	char	*cmd_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		new_cmd = ft_strjoin("/", cmd);
		cmd_path = ft_strjoin(path_dirs[i], new_cmd);
		free(new_cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free_split(path_dirs);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*check_command_existence(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (cmd);
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, char **env)
{
	char	*path;
	char	**path_dirs;
	char	*cmd_path;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	if (check_command_existence(cmd) != NULL)
		return (ft_strdup(cmd));
	path = find_path_env(env);
	if (!path)
		return (NULL);
	path_dirs = ft_split(path, ':');
	free(path);
	if (!path_dirs)
		return (NULL);
	cmd_path = try_path(path_dirs, cmd);
	if (!cmd_path)
		free_split(path_dirs);
	return (cmd_path);
}
