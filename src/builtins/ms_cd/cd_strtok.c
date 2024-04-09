/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:01:09 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 11:35:24 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_string.h"

static char	*get_next_word(char *s, const char *delim);

char	*cd_strtok(char *s, const char *delim)
{
	static char	*str = NULL;
	char		*rvalue;

	if (s)
	{
		str = s;
		while (*str && ft_strchr(delim, *str))
			++str;
		if (*str == '\0')
			str = NULL;
	}
	if (str)
	{
		rvalue = str;
		str = get_next_word(str, delim);
		return (rvalue);
	}
	return (NULL);
}

static char	*get_next_word(char *s, const char *delim)
{
	while (*s && ft_strchr(delim, *s) == NULL)
		++s;
	while (*s && ft_strchr(delim, *s))
	{
		*s = '\0';
		++s;
	}
	if (*s == '\0')
		s = NULL;
	return (s);
}
