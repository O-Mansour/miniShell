/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:06:30 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 22:02:16 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	searsh_path(char *key)
{
	t_env	*tmp;

	tmp = g_minishell.env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_get_path_(char *cmd, char **path)
{
	int		i;
	char	*s;

	i = 0;
	while (path && path[i])
	{
		s = ft_strjoin(path[i], cmd);
		if (access(s, F_OK) == 0)
			ft_error(cmd, ": permission denied\n", 126);
		free(s);
		i++;
	}
	ft_error(cmd, ": command not found\n", 127);
}

char	*ft_get_pth(char **path, char *cmd)
{
	int		i;
	char	*s;
	DIR		*dir;

	i = 0;
	while (path && path[i])
	{
		s = ft_strjoin(path[i], cmd);
		dir = opendir(s);
		if (dir)
			ft_error(cmd, ": command not found\n", 127);
		if (access(s, F_OK | X_OK) == 0)
			return (s);
		free(s);
		i++;
	}
	ft_get_path_(cmd, path);
	return (0);
}
