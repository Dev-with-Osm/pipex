/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:07:48 by okhourss          #+#    #+#             */
/*   Updated: 2025/01/27 21:07:49 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*dup_str;

	if (!str)
		return (0);
	i = 0;
	dup_str = malloc(ft_strlen(str) + 1);
	if (!dup_str)
		return (NULL);
	while (str[i])
	{
		dup_str[i] = str[i];
		i++;
	}
	dup_str[i] = '\0';
	return (dup_str);
}
