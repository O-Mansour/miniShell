/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:59:55 by omansour          #+#    #+#             */
/*   Updated: 2023/07/20 19:17:21 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_flag(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-' && str[i + 1] == 'n')
		i++;
	else
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo(t_args *cmmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = ft_flag(cmmd->cmd[i]);
	while (!ft_flag(cmmd->cmd[i]))
		i++;
	while (cmmd->cmd[i])
	{
		ft_putstr_fd(cmmd->cmd[i++], cmmd->outfile);
		if (cmmd->cmd[i])
			ft_putstr_fd(" ", cmmd->outfile);
	}
	if (flag == 1)
		ft_putstr_fd("\n", cmmd->outfile);
}
