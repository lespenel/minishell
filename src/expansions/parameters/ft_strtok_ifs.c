/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_ifs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 05:37:07 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/06 05:37:56 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

static char	*get_next_word_ifs(char *s, const char *delim);

char	*ft_strtok_ifs(char *s, const char *delim)
{
	static char	*str = NULL;
	char		*rvalue;

	if (s)
	{
		str = s;
		if (*str == '\0')
			str = NULL;
	}
	if (str)
	{
		rvalue = str;
		str = get_next_word_ifs(str, delim);
		return (rvalue);
	}
	return (NULL);
}

static char	*get_next_word_ifs(char *s, const char *delim)
{
	while (*s && ft_strchr(delim, *s) == NULL)
		++s;
	while (*s && ft_strchr(" \t\n", *s) && ft_strchr(delim, *s))
	{
		*s = '\0';
		++s;
	}
	if (*s && ft_strchr(delim, *s))
	{
		*s = '\0';
		++s;
	}
	while (*s && ft_strchr(" \t\n", *s) && ft_strchr(delim, *s))
	{
		*s = '\0';
		++s;
	}
	if (*s == '\0')
		s = NULL;
	return (s);
}
