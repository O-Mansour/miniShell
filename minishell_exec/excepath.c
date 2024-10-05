/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excepath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:57:24 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 12:47:00 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *arg1, char *arg2, int ex)
{
	ft_putstr_fd("minishell: ", 2);
	if (arg1)
		ft_putstr_fd(arg1, 2);
	if (arg2)
		ft_putstr_fd(arg2, 2);
	if (ex)
		exit(ex);
}

char	*check_path(void)
{
	t_env	*env;

	env = g_minishell.env;
	while (env)
	{
		if (ft_strcmp("PATH", env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	**full_path(void)
{
	char	**path;
	char	*str;
	int		i;

	str = check_path();
	if (!str)
		return (0);
	path = ft_split(str, ':');
	i = 0;
	while (path[i])
	{
		str = path[i];
		path[i] = ft_strjoin(str, "/");
		free(str);
		str = NULL;
		i++;
	}
	return (path);
}

char	**full_env(void)
{
	char	**env;
	char	*s;
	t_env	*it;
	int		i;

	it = g_minishell.env;
	if (!ft_lstsize_env(it))
		return (0);
	env = malloc(sizeof(char *) * (ft_lstsize_env(it) + 1));
	if (!env)
		return (NULL);
	i = -1;
	while (it)
	{
		env[++i] = ft_strdup(it->key);
		if (it->value)
		{
			s = ft_strjoin(env[i], "=");
			free(env[i]);
			env[i] = ft_strjoin(s, it->value);
			free(s);
		}
		it = it->next;
	}
	return (env[++i] = NULL, env);
}

void	get_env(char **env)
{
	int		i;
	char	**line;
	char	*value;

	if (!env || !*env)
		return ;
	i = 0;
	while (env[i])
	{
		line = ft_split(env[i], '=');
		if (ft_strchr(env[i], '='))
			value = ft_strdup(ft_strchr(env[i], '=') + 1);
		else
			value = NULL;
		ft_lstadd_backk(&g_minishell.env, ft_lstneew(ft_strdup(line[0]),
				value));
		ft_free(line);
		i++;
	}
}
