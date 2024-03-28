/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:08:32 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/28 04:40:18 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"
#include "hashmap.h"
#include "vector.h"

static int	add_pairs(t_vector *envp, t_vector *vars);

char	**get_envp(t_env *env)
{
	size_t		i;
	t_vector	envp;

	init_vector(&envp, sizeof(char *));
	i = 0;
	while (i < HASHMAP_SIZE)
	{
		if (add_pairs(&envp, env->map + i) == -1)
		{
			clear_vector(&envp);
			return (NULL);
		}
		++i;
	}
	return (envp.array);
}

static int	add_pairs(t_vector *envp, t_vector *vars)
{
	size_t	j;
	char	*s;
	t_pair	*pair;

	j = 0;
	while (j < vars->size)
	{
		pair = at_vector(vars, j);
		s = ft_strjoin_three(pair->key, "=", pair->value);
		if (s == NULL)
			return (-1);
		if (add_vector(envp, &s, 1) == -1)
			return (-1);
		++j;
	}
	return (0);
}
