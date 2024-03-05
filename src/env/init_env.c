/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:55:53 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/04 10:05:57 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"
#include "hashmap.h"
#include <stdlib.h>

int	init_env(t_env *env, char *envp[])
{
	char	*value;

	init_hashmap(env);
	while (*envp)
	{
		value = ft_strtok(*envp, "=");
		value = ft_strtok(NULL, "=");
		if (value)
			ms_setenv(env, *envp, value);
		++envp;
	}
	return (0);
}
