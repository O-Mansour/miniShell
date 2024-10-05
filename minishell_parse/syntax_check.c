/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:58:52 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 17:56:30 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nothing_before_pipe(char *str, int i)
{
	while (--i >= 0)
	{
		if (str[i] == '|')
			return (1);
		if (str[i] != ' ' && (str[i] < 9 || str[i] > 13))
			return (0);
	}
	return (1);
}

int	nothing_after_pipe(char *str, int i)
{
	while (str[++i])
	{
		if (str[i] == '|')
			return (1);
		if (str[i] != ' ' && (str[i] < 9 || str[i] > 13))
			return (0);
	}
	return (1);
}

int	second_quote(char *str, int i, int c)
{
	while (str[++i])
	{
		if (str[i] == c)
			break ;
	}
	if (str[i])
		return (i);
	return (0);
}

int	ft_isspace(char c)
{
	if (c != ' ' && (c < 9 || c > 13))
		return (0);
	return (1);
}
