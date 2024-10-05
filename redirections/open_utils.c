/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:32:38 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 20:54:22 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_real_input(t_files *curr)
{
	char	*real_input;

	real_input = NULL;
	while (curr)
	{
		if (curr->type == RED_IN)
		{
			if (real_input)
				free(real_input);
			real_input = ft_strdup(curr->word);
		}
		else if (curr->type == HERE_DOC)
		{
			if (real_input)
				free(real_input);
			real_input = NULL;
		}
		curr = curr->next;
	}
	return (real_input);
}
