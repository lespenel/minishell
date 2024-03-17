/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:38:01 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/17 04:30:10 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "env.h"
#include <unistd.h>

int	ms_echo(t_env *env, char **args)
{
	size_t	i;
	size_t	argc;
	int		no_nl;

	(void)env;
	no_nl = 0;
	argc = 0;
	while (args[argc])
		argc++;
	if (argc >= 2 && ft_strncmp(args[1], "-n", 2) == 0)
		no_nl = 1;
	if (argc == 2 && no_nl)
		return (0);
	i = 1 + no_nl;
	while (i < argc)
	{
		if (write(1, args[i], ft_strlen(args[i])) == -1)
			return (-1);
		if (i < argc - 1 && write(1, " ", 1) == -1)
			return (-1);
		++i;
	}
	if (no_nl == 0 && write(1, "\n", 1) == -1)
		return (-1);
	return (0);
}
