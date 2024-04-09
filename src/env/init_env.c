/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:55:53 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/09 02:39:05 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

static int	add_variable(t_env *env, char *str);

int	init_env(t_env *env, char *envp[])
{
	init_hashmap(env);
	while (*envp)
	{
		if (add_variable(env, *envp) == -1)
		{
			destroy_hashmap(env);
			return (-1);
		}
		++envp;
	}
	return (0);
}

static int	add_variable(t_env *env, char *str)
{
	char	*currentvar;
	char	*value;

	currentvar = ft_strdup(str);
	if (currentvar == NULL)
		return (-1);
	value = ft_strtok(currentvar, "=");
	value = ft_strtok(NULL, "=");
	if (value)
	{
		if (ms_setenv(env, currentvar, value) == -1)
		{
			free(currentvar);
			return (-1);
		}
	}
	free(currentvar);
	return (0);
}
