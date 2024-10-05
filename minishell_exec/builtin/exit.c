/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:00:07 by omansour          #+#    #+#             */
/*   Updated: 2023/07/29 12:37:49 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valid_str(char *str, int i)
{
	unsigned long	n;

	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - 48;
		if (n > 9223372036854775807)
			ft_error(str, ": numeric argument required\n", 255);
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		ft_error(str, ": numeric argument required\n", 255);
	return (n);
}

int	ft_atoi_check(char *str)
{
	int	i;
	int	s;

	i = 0;
	s = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = s * (-1);
		i++;
	}
	if (!str[i])
		ft_error(str, ": numeric argument required\n", 255);
	return (valid_str(str, i) * s);
}

void	ft_exit(t_args *cmmd)
{
	int	i;

	i = 0;
	if (cmmd->cmd[i] && cmmd->cmd[i + 1] && !cmmd->cmd[i + 2])
	{
		g_minishell.exit_code = ft_atoi_check(cmmd->cmd[i + 1]);
		exit(g_minishell.exit_code);
	}
	else if (cmmd->cmd[i] && cmmd->cmd[i + 1] && cmmd->cmd[i + 2])
	{
		ft_atoi_check(cmmd->cmd[i + 1]);
		g_minishell.exit_code = 1;
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
	}
	else
		exit(g_minishell.exit_code);
}
