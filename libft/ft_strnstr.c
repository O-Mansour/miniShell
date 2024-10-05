/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omansour <omansour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:37:31 by omansour          #+#    #+#             */
/*   Updated: 2022/11/01 03:19:12 by omansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(needle[0]))
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		while (haystack[i + j] && needle[j] == haystack[i + j] && i + j < len)
		{
			j++;
			if (!(needle[j]))
				return ((char *)haystack + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
