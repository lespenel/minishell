/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 06:19:33 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/09 05:41:29 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "env.h"
#include "hashmap.h"
#include "vector.h"
#include <stdio.h>

int	print_env(t_env *env)
{
	size_t		i;
	size_t		j;
	t_vector	*vector;
	t_pair		*pair;

	i = 0;
	while (i < HASHMAP_SIZE)
	{
		vector = env->map + i;
		j = 0;
		while (j < vector->size)
		{
			pair = at_vector(vector, j);
			if (ft_dprintf(1, "%s=%s\n", pair->key, pair->value) == -1)
				return (-1);
			++j;
		}
		++i;
	}
	return (0);
}
