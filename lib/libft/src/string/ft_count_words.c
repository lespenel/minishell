/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:35:29 by ccouble           #+#    #+#             */
/*   Updated: 2023/12/26 13:43:00 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_string.h"

size_t	ft_count_words(char *s, char *delim)
{
	size_t	count;

	count = 0;
	while (*s && ft_strchr(delim, *s))
		++s;
	while (*s)
	{
		++count;
		while (*s && ft_strchr(delim, *s) == NULL)
			++s;
		while (*s && ft_strchr(delim, *s))
			++s;
	}
	return (count);
}
