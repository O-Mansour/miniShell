/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:44:21 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 20:44:52 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **str_p)
{
	int	i;

	i = 0;
	if (!str_p)
		return ;
	while (str_p[i])
	{
		free(str_p[i]);
		str_p[i] = NULL;
		i++;
	}
	free(str_p);
	str_p = NULL;
}

int	cmp_str(char *s1, char *s2)
{
	unsigned int	i;

	i = -1;
	if (!s1 || !s2)
		return (0);
	while (s1[++i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
	}
	return (1);
}
