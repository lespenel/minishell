/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 04:57:11 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/14 23:55:25 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "vector.h"
#include <stdlib.h>

int	ft_split_vector(t_vector *dest, char *s, char *delim)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i + j] && ft_strchr(delim, s[i + j]) == NULL)
			++j;
		if (j != 0)
		{
			tmp = ft_strndup(s + i, j);
			if (tmp == NULL)
				return (-1);
			if (add_vector(dest, &tmp, 1) == -1)
			{
				free(tmp);
				return (-1);
			}
			i += j - 1;
		}
		++i;
	}
	return (0);
}
