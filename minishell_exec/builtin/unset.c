/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:00:11 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 21:41:53 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env(t_env *e)
{
	free(e->key);
	free(e->value);
	free(e);
}

void	ft_list_remove(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*t;

	tmp = *env;
	if (!tmp)
		return ;
	if (ft_strcmp(tmp->key, key) == 0)
	{
		(*env) = (*env)->next;
		free_env(tmp);
		return ;
	}
	t = tmp;
	tmp = tmp->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			t->next = tmp->next;
			free_env(tmp);
			return ;
		}
		t = tmp;
		tmp = tmp->next;
	}
}

int	check_chars(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (1);
	i++;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (!cmd[i][0])
		{
			i++;
			continue ;
		}
		else if (check_chars(cmd[i]))
		{
			g_minishell.exit_code = 1;
			ft_error(*cmd, ": not a valid identifier\n", 0);
		}
		else
			ft_list_remove(&g_minishell.env, cmd[i]);
		i++;
	}
}
