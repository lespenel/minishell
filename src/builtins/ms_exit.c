/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:05:13 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/18 06:03:50 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/readline.h>

static int	get_exit_code(char *nptr);
static int	free_exit(t_minishell *ms, t_lexer *lexer, char **args, int ret);

int	ms_exit(t_minishell *minishell, t_lexer *lexer, char **args)
{
	const int	argc = get_argc(args);
	int			ret;

	if (argc == 1)
		free_exit(minishell, lexer, args, 0);
	else
	{
		ret = get_exit_code(args[1]);
		if (ret == -1)
		{
			ret = write(2, "minishell: exit: numeric argument required\n", 44);
			free_exit(minishell, lexer, args, 2);
		}
		if (argc == 2)
			free_exit(minishell, lexer, args, ret);
	}
	if (write(1, "exit\n", 5) == -1
		|| write(2, "minishell: exit: too many arguments\n", 36) == -1)
		return (-1);
	return (127);
}

static int	free_exit(t_minishell *ms, t_lexer *lexer, char **args, int ret)
{
	clear_lexer(lexer);
	destroy_env(&ms->env);
	rl_clear_history();
	clear_args(args);
	write(1, "exit\n", 5);
	exit(ret);
}

static int	get_exit_code(char *nptr)
{
	const size_t	len = ft_strlen(nptr);
	long int		nb;
	size_t			i;

	if (len == 20 && ft_strcmp(nptr, "-9223372036854775808") == 0)
		return (0);
	i = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
		++i;
	if (nptr[i] < '0' || nptr[i] > '9')
		return (-1);
	nb = 0;
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		if (LONG_MAX / 10 < nb || LONG_MAX - (nptr[i] - '0') < nb * 10)
			return (-1);
		nb = nb * 10 + (nptr[i] - '0');
		++i;
	}
	if (len != i)
		return (-1);
	if (nptr[0] == '-')
		return ((LONG_MAX - nb + 1) % 256);
	return (nb % 256);
}
