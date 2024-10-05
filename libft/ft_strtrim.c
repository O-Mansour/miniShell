/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:48:38 by omansour          #+#    #+#             */
/*   Updated: 2022/11/01 03:19:41 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	ssize_t		i;
	ssize_t		j;
	char		*p;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	if (s1[i] == '\0')
		return (ft_strdup(""));
	j = ft_strlen(s1) - 1;
	while (ft_strchr((char *) set, s1[i]))
		i++;
	while (ft_strrchr((char *) set, s1[j]))
		j--;
	if (j < i)
		return (ft_strdup(""));
	p = malloc (j - i + 2);
	if (!p)
		return (NULL);
	ft_strlcpy (p, s1 + i, j - i + 2);
	return (p);
}
