/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_escaping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:05:24 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/20 00:05:40 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "ft_string.h"

int	add_escaping(t_vector *vector, char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr("\\'\"", s[i]))
		{
			if (add_vector(vector, "\\", 1) == -1)
				return (-1);
		}
		if (add_vector(vector, s + i, 1) == -1)
			return (-1);
		++i;
	}
	return (0);
}
