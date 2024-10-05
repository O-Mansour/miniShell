/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:41:04 by omansour          #+#    #+#             */
/*   Updated: 2023/07/28 16:44:35 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	swap(t_env *x, t_env *y)
{
	char	*value;
	char	*key;

	key = x->key;
	value = x->value;
	x->key = y->key;
	x->value = y->value;
	y->key = key;
	y->value = value;
}

void	soirt_exp(void)
{
	t_env	*tmp;
	t_env	*tmp1;

	tmp = g_minishell.env;
	while (tmp && tmp->next != NULL)
	{
		tmp1 = tmp;
		while (tmp1 && tmp1->next != NULL)
		{
			if (ft_strcmp(tmp->key, tmp1->next->key) > 0)
				swap(tmp, tmp1->next);
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
}

void	print_export(t_args *cmd)
{
	t_env	*it;

	if (fork() == 0)
	{
		soirt_exp();
		it = g_minishell.env;
		while (it)
		{
			if (it->value == NULL)
			{
				ft_putstr_fd("declare -x ", cmd->outfile);
				ft_putstr_fd(it->key, cmd->outfile);
				ft_putstr_fd("\n", cmd->outfile);
			}
			else
			{
				setup_eport(cmd, it);
			}
			it = it->next;
		}
		exit(0);
	}
	else
		wait(NULL);
}

void	addenv(char *key, char *value)
{
	t_env	*tmp;

	tmp = g_minishell.env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			if (value)
				value = ft_strdup(value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return ;
	tmp->key = ft_strdup(key);
	if (value)
		value = ft_strdup(value);
	tmp->value = value;
	tmp->next = NULL;
	ft_lstadd_backk(&g_minishell.env, tmp);
}

void	app_new_value(char *key, char *value)
{
	t_env	*tmp;

	tmp = g_minishell.env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
				value = ft_strjoin(tmp->value, value);
			else
				value = ft_strdup(value);
			if (tmp->value)
				free(tmp->value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	addenv(key, value);
}
