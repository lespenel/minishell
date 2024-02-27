/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:08:03 by ccouble           #+#    #+#             */
/*   Updated: 2024/02/27 02:54:06 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include <stdlib.h>

static int		count_seps(const char *s, char c);
static size_t	get_word(char **strs, const char *str, char s, int count);
static void		*free_all(char **strs);

char	**ft_split(const char *s, char c)
{
	size_t	i;
	size_t	count;
	char	**strs;

	while (*s == c && *s)
		++s;
	if (*s == '\0')
		return (ft_calloc(1, sizeof(char *)));
	count = count_seps(s, c);
	strs = ft_calloc(count + 2, sizeof(char *));
	if (strs == NULL)
		return (NULL);
	i = 0;
	while (i < count + 1)
	{
		s += get_word(strs, s, c, i);
		if (strs[i] == NULL)
			return (free_all(strs));
		++i;
	}
	return (strs);
}

static int	count_seps(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
		{
			while (*s == c)
				++s;
			if (*s == '\0')
				return (count);
			--s;
			++count;
		}
		++s;
	}
	return (count);
}

static size_t	get_word(char **strs, const char *str, char s, int count)
{
	size_t	i;

	i = 0;
	while (str[i] != s && str[i])
		++i;
	strs[count] = ft_calloc(i + 1, sizeof(char));
	if (strs[count] == NULL)
		return (0);
	ft_memcpy(strs[count], str, i);
	while (str[i] == s)
		++i;
	return (i);
}

static void	*free_all(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		++i;
	}
	free(strs);
	return (NULL);
}
