/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdex.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:27:49 by omansour          #+#    #+#             */
/*   Updated: 2023/07/27 12:29:57 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	oldpwdd(t_args *cmds)
{
	char	*old;

	old = ft_check_env("OLDPWD");
	if (!old)
		return ;
	chdir(old);
	change_pwd_oldpwd();
	ft_putstr_fd(old, cmds->outfile);
	ft_putstr_fd("\n", cmds->outfile);
}

void	ft_cd(t_args *cmds)
{
	char	*home;

	if (cmds->cmd[1] == NULL || !ft_strcmp(cmds->cmd[1], "~"))
	{
		home = ft_check_env("HOME");
		if (!home)
			return ;
		if (chdir(home) == -1)
			return ;
		change_pwd_oldpwd();
	}
	else if (!ft_strcmp(cmds->cmd[1], "-"))
		oldpwdd(cmds);
	else
		chdirtest(cmds);
}
