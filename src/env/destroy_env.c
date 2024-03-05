/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 06:07:38 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/04 08:13:44 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "hashmap.h"
#include "vector.h"
#include <stdlib.h>

void	destroy_env(t_env *env)
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
			free(pair->key);
			free(pair->value);
			++j;
		}
		++i;
	}
	destroy_hashmap(env);
}
