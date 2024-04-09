/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:38:01 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 05:47:26 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_string.h"
#include <stddef.h>
#include <unistd.h>

int	ms_echo(t_env *env, char **args)
{
	const int	argc = get_argc(args);
	int			no_nl;
	int			i;
	ssize_t		len;

	(void)env;
	no_nl = 0;
	if (argc >= 2 && ft_strcmp(args[1], "-n") == 0)
		no_nl = 1;
	if (argc == 2 && no_nl)
		return (0);
	i = 1 + no_nl;
	while (i < argc)
	{
		len = ft_strlen(args[i]);
		if (write(1, args[i], len) != len)
			return (1);
		if (i < argc - 1 && write(1, " ", 1) != 1)
			return (1);
		++i;
	}
	if (no_nl == 0 && write(1, "\n", 1) != 1)
		return (1);
	return (0);
}
