/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:41:10 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 20:41:48 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_backk(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	new->next = NULL;
}

void	close_after_use(t_args *cmds)
{
	if (cmds->infile && cmds->infile != -1)
		close(cmds->infile);
	if (cmds->outfile != 1 && cmds->outfile != -1)
		close(cmds->outfile);
}
