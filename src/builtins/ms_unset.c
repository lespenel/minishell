/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 04:10:46 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/18 03:30:04 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	ms_unset(t_env *env, char **args)
{
	int	argc;

	argc = 0;
	(void)env;
	while (args[argc])
		argc++;
	if (argc == 1)
		return (0);
	return (0);
}
