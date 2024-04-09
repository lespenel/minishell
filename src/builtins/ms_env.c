/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 04:02:02 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 05:42:47 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <unistd.h>

int	ms_env(t_env *env, char **args)
{
	int	argc;

	argc = 0;
	while (args[argc])
		argc++;
	if (argc != 1)
	{
		if (write(2, "minishell: env: to many arguments\n", 35) != 35)
			return (1);
		return (1);
	}
	if (print_env(env) == -1)
		return (1);
	return (0);
}
