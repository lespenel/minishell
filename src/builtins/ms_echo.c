/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:38:01 by lespenel          #+#    #+#             */
/*   Updated: 2024/05/03 06:17:47 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include <unistd.h>

static int	echo_cmp(char *str);

int	ms_echo(t_ms *ms, char **args)
{
	const int	argc = get_argc(args);
	int			no_nl;
	int			i;
	ssize_t		len;

	(void)ms;
	no_nl = 0;
	i = 1;
	while (i < argc)
	{
		if (echo_cmp(args[i]))
		{
			no_nl = 1;
			++i;
			continue ;
		}
		len = ft_strlen(args[i]);
		if (write(1, args[i], len) != len
			|| (i < argc - 1 && write(1, " ", 1) != 1))
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
