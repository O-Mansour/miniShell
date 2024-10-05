/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:54:17 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 20:59:20 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_nwords(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i])
			n++;
		while (str[i] && !ft_isspace(str[i]))
		{
			if (str[i] == '>' || str[i] == '<')
				ft_nwords_help(str, &i, &n);
			else if (str[i] == '"' || str[i] == '\'')
				i = second_quote(str, i, str[i]);
			i++;
		}
	}
	return (n);
}

static char	**ft_deallocate(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static void	skip_redirec(char *str, int *x)
{
	while (str[*x] == '>' || str[*x] == '<')
		(*x)++;
}

static char	**ft_fill(char *str, char **strs)
{
	int	x;
	int	y;
	int	z;

	x = 0;
	z = 0;
	while (str[x])
	{
		ft_fill_help(str, &x, &y);
		if (x > y)
		{
			strs[z] = ft_substr(str, y, x - y);
			if (!strs[z++])
				return (ft_deallocate(strs));
		}
		y = x;
		if (str[x] == '>' || str[x] == '<')
		{
			skip_redirec(str, &x);
			strs[z] = ft_substr(str, y, x - y);
			if (!strs[z++])
				return (ft_deallocate(strs));
		}
	}
	return (strs);
}

char	**split_proc(char *s)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = (char **) calloc(ft_nwords(s) + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	strs = ft_fill(s, strs);
	return (strs);
}
