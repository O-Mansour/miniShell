/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:54:52 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 17:56:04 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	invalid_before_redirection(char *str, int i)
{
	while (--i >= 0)
	{
		if (str[i] == '<' || str[i] == '>')
			return (1);
		if (str[i] != ' ' && (str[i] < 9 || str[i] > 13))
			return (0);
	}
	return (0);
}

int	invalid_after_redirection(char *str, int i)
{
	while (str[++i])
	{
		if (str[i] == '|')
			return (1);
		if (str[i] == '<' || str[i] == '>')
			return (1);
		if (str[i] != ' ' && (str[i] < 9 || str[i] > 13))
			return (0);
	}
	return (1);
}

int	invalid_redirec(char *str, int *i)
{
	if (invalid_before_redirection(str, *i))
		return (1);
	if ((str[*i] == '<' && str[*i + 1] == '>')
		|| (str[*i] == '>' && str[*i + 1] == '<'))
		return (1);
	if (str[*i + 1] == '<' || str[*i + 1] == '>')
		(*i)++;
	if (invalid_after_redirection(str, *i))
		return (1);
	return (0);
}

int	syntax_err(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = second_quote(str, i, str[i]);
			if (!i)
				return (1);
		}
		else if (str[i] == '|')
		{
			if (nothing_before_pipe(str, i) || nothing_after_pipe(str, i))
				return (1);
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (invalid_redirec(str, &i))
				return (1);
		}
		i++;
	}
	return (0);
}
