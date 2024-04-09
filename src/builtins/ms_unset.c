/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 04:10:46 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/10 00:43:09 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"

int	ms_unset(t_env *env, char **args)
{
	const int	argc = get_argc(args);
	int			i;

	(void)env;
	if (argc == 1)
		return (0);
	i = 1;
	while (i < argc)
	{
		++i;
	}
	return (0);
}
