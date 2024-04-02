/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:08:03 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/02 05:08:34 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include "ft_string.h"
#include <stdio.h>
#include <stdlib.h>

char	**ft_split(const char *s, char *delim)
{
	size_t	count;
	char	**strs;
	size_t	i;
	size_t	j;

	while (*s && ft_strchr(delim, *s))
		++s;
	count = ft_count_words(s, delim);
	strs = malloc((count + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	strs[count] = NULL;
	count = 0;
	i = 0;
	while (s[i])
	{
		j = i;
		while (s[i] && ft_strchr(delim, s[i]) == NULL)
			++i;
		strs[count] = malloc(((i - j) + 1) * sizeof(char));
		if (strs[count] == NULL)
		{
			ft_free_strs(strs, count);
			return (NULL);
		}
		strs[count][i - j] = '\0';
		ft_memcpy(strs[count], s + j, (i - j) * sizeof(char));
		while (s[i] && ft_strchr(delim, s[i]))
			++i;
		++count;
	}
	return (strs);
}
