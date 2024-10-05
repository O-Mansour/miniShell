/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:29:05 by omansour          #+#    #+#             */
/*   Updated: 2023/08/04 07:31:07 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	use_env_path(t_args *cmmd)
{
	t_env	*tmp;

	tmp = g_minishell.env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			ft_putendl_fd(tmp->value, cmmd->outfile);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_pwd(t_args *cmmd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(cwd, cmmd->outfile);
		ft_putstr_fd("\n", cmmd->outfile);
		free(cwd);
	}
	else
		use_env_path(cmmd);
}
