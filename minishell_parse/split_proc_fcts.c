/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_proc_fcts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:49:25 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 21:01:29 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nb_procs(char *str)
{
	int	i;
	int	nb;

	i = -1;
	nb = 1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = second_quote(str, i, str[i]);
		else if (str[i] == '|')
			nb++;
	}
	return (nb);
}

void	ft_nwords_help(char *str, int *i, int *n)
{
	if (*i != 0 && str[*i - 1] != ' ')
		(*n)++;
	if (str[*i + 1] == '>' || str[*i + 1] == '<')
		(*i)++;
	if (str[*i + 1] != ' ')
		(*n)++;
}

void	ft_fill_help(char *str, int *x, int *y)
{
	while (str[*x] && ft_isspace(str[*x]))
		(*x)++;
	*y = *x;
	while (str[*x] && !ft_isspace(str[*x]) && str[*x] != '>' && str[*x] != '<')
	{
		if (str[*x] == '"' || str[*x] == '\'')
			*x = second_quote(str, *x, str[*x]);
		(*x)++;
	}
}
