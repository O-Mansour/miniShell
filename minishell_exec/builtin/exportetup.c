/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportetup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:50:35 by omansour          #+#    #+#             */
/*   Updated: 2023/07/28 16:56:35 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setup_eport(t_args *cmd, t_env *it)
{
	ft_putstr_fd("declare -x ", cmd->outfile);
	ft_putstr_fd(it->key, cmd->outfile);
	ft_putstr_fd("=\"", cmd->outfile);
	ft_putstr_fd(it->value, cmd->outfile);
	ft_putstr_fd("\"\n", cmd->outfile);
}
