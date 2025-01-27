/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:50:06 by okhourss          #+#    #+#             */
/*   Updated: 2025/01/27 09:33:16 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	execute_cmd(char *cmd, char **env);
void	second_child_process(int *fd, const char *outfile, const char *cmd,
			char **env);
void	child_process(int *fd, const char *infile, const char *cmd, char **env);
void	cleanup_and_exit(char *error_msg, int exit_code);
void	free_split(char **arr);
char	*find_path_env(char **env);
char	*try_path(char **path_dirs, char *cmd);
char	*check_command_existence(char *cmd);
char	*get_command_path(char *cmd, char **env);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s,
			unsigned int start, size_t len);

#endif
