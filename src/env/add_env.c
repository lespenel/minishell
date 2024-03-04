/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 07:58:36 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/04 08:05:36 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"
#include <stdlib.h>

int	add_env(t_env *env, char *key, char *value)
{
	key = ft_strdup(key);
	if (key == NULL)
		return (-1);
	value = ft_strdup(value);
	if (value == NULL)
	{
		free(key);
		return (-1);
	}
	if (setvalue_hashmap(env, key, value) == -1)
	{
		free(key);
		free(value);
		return (-1);
	}
	return (0);
}
