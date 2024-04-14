/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:38:01 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/14 14:31:38 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_string.h"
#include <unistd.h>

static int	echo_cmp(char *str);

int	ms_echo(t_env *env, char **args)
{
	const int	argc = get_argc(args);
	int			no_nl;
	int			i;
	ssize_t		len;

	(void)env;
	no_nl = 0;
	if (argc >= 2 && echo_cmp(args[1]))
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

static int	echo_cmp(char *str)
{
	size_t	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		++i;
	}
	return (i >= 2);
}
