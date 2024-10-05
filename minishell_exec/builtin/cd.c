/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:59:50 by omansour          #+#    #+#             */
/*   Updated: 2023/07/31 11:11:35 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_check_env(char *str)
{
	t_env	*tmp;

	tmp = g_minishell.env;
	if (!str)
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
		{
			if (tmp->value)
				return (tmp->value);
		}
		tmp = tmp->next;
	}
	g_minishell.exit_code = 1;
	ft_error("cd: ", str, 0);
	ft_putstr_fd(" not set\n", 2);
	return (0);
}

void	oldpwd(char *p)
{
	t_env	*tmp;

	tmp = g_minishell.env;
	while (g_minishell.env)
	{
		if (ft_strcmp(g_minishell.env->key, "OLDPWD") == 0)
		{
			if (g_minishell.env->value)
				free(g_minishell.env->value);
			g_minishell.env->value = p;
			break ;
		}
		g_minishell.env = g_minishell.env->next;
		if (!g_minishell.env)
		{
			if (p)
				free(p);
		}
	}
	g_minishell.env = tmp;
}

void	change_pwd_oldpwd(void)
{
	t_env	*tmp;
	char	*p;
	char	*pwd;

	p = NULL;
	tmp = g_minishell.env;
	pwd = getcwd(NULL, 0);
	while (g_minishell.env)
	{
		if (ft_strcmp(g_minishell.env->key, "PWD") == 0)
		{
			p = g_minishell.env->value;
			g_minishell.env->value = pwd;
			break ;
		}
		g_minishell.env = g_minishell.env->next;
		if (!g_minishell.env)
			free(pwd);
	}
	g_minishell.env = tmp;
	oldpwd(p);
}

void	res(void)
{
	char	*pwd;

	change_pwd_oldpwd();
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return ;
	}
	if (pwd)
		free(pwd);
}

void	chdirtest(t_args *cmds)
{
	int		result;

	result = chdir(cmds->cmd[1]);
	if (result == 0)
		res();
	else if (!access(cmds->cmd[1], F_OK))
	{
		g_minishell.exit_code = 1;
		ft_error("cd: ", cmds->cmd[1], 0);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else
	{
		g_minishell.exit_code = 1;
		ft_error("cd: ", cmds->cmd[1], 0);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}
