/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:29:43 by omansour          #+#    #+#             */
/*   Updated: 2023/07/28 16:24:17 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_key(char *key)
{
	t_env	*tmp;

	tmp = g_minishell.env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return ;
		tmp = tmp->next;
	}
	addenv(key, NULL);
}

void	ft_app(char *cmd)
{
	char	*value;
	char	**tmp;

	tmp = ft_split(cmd, '+');
	if (!tmp)
		return ;
	value = ft_strchr(cmd, '+');
	value += 2;
	app_new_value(tmp[0], value);
	ft_free(tmp);
}

int	check(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] != '_' && !ft_isalpha(cmd[i]))
		return (1);
	i++;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (2);
		if (cmd[i] == '+' && cmd[i + 1] == '=')
			return (3);
		if (cmd[i] != '_' && !ft_isalnum(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

void	add_exp(char **cmd)
{
	int	i;
	int	type;

	i = 1;
	while (cmd[i])
	{
		type = check(cmd[i]);
		if (type == 1)
		{
			g_minishell.exit_code = 1;
			ft_error(*cmd, ": not a valid identifier\n", 0);
		}
		else if (type == 0)
			add_key(cmd[i]);
		else if (type == 2)
			ft_add(cmd[i]);
		else if (type == 3)
			ft_app(cmd[i]);
		i++;
	}
}

void	ft_export(t_args *cmd)
{
	if (cmd->cmd[1] == NULL)
		print_export(cmd);
	else
		add_exp(cmd->cmd);
}
