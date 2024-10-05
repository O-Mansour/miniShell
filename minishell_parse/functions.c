/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:19:44 by omansour          #+#    #+#             */
/*   Updated: 2023/07/30 20:44:47 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_nwords(char *str, char c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
			n++;
		while (str[i] && (str[i] != c))
		{
			if (str[i] == '"' || str[i] == '\'')
				i = second_quote(str, i, str[i]);
			i++;
		}
	}
	return (n);
}

static char	**ft_deallocate(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static char	**ft_fill(char *str, char **strs, char c)
{
	size_t	x;
	size_t	y;
	size_t	z;

	x = 0;
	z = 0;
	while (str[x])
	{
		while (str[x] && str[x] == c)
			x++;
		if (str[x] && str[x] != c)
		{
			y = x;
			while (str[x] && str[x] != c)
			{
				if (str[x] == '"' || str[x] == '\'')
					x = second_quote(str, x, str[x]);
				x++;
			}
			strs[z] = ft_substr(str, y, x - y);
			if (!strs[z++])
				return (ft_deallocate(strs));
		}
	}
	return (strs);
}

char	**split_ignore_quotes(char *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = (char **) ft_calloc(ft_nwords(s, c) + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	strs = ft_fill(s, strs, c);
	return (strs);
}

char	*str_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*p;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!p)
		return (0);
	i = -1;
	j = 0;
	while (s1[++i])
		p[i] = s1[i];
	p[i++] = ' ';
	while (s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	free (s1);
	return (p);
}
