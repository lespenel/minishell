/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:05:13 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/16 08:20:04 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_char.h"
#include "ft_string.h"
#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/readline.h>

static int	get_exit_code(char *nptr);
static int	free_exit(t_ms *ms, t_lexer_tok *token, char **args, int ret);

int	ms_exit(t_ms *minishell, t_lexer_tok *token, char **args)
{
	const int	argc = get_argc(args);
	int			ret;

	if (argc == 1)
		free_exit(minishell, token, args, minishell->lastexit);
	else
	{
		ret = get_exit_code(args[1]);
		if (ret == -1)
		{
			ret = write(2, "minishell: exit: numeric argument required\n", 44);
			free_exit(minishell, token, args, 2);
		}
		if (argc == 2)
			free_exit(minishell, token, args, ret);
	}
	if (write(STDERR_FILENO, "exit\n", 5) == -1
		|| write(2, "minishell: exit: too many arguments\n", 36) == -1)
		return (1);
	return (1);
}

static int	free_exit(t_ms *ms, t_lexer_tok *token, char **args, int ret)
{
	int	w;

	(void)args;
	clear_token(token);
	destroy_minishell(ms);
	rl_clear_history();
	w = write(STDERR_FILENO, "exit\n", 5);
	(void)w;
	exit(ret);
}

static int	get_exit_code(char *nptr)
{
	const size_t	len = ft_strlen(nptr);
	long int		nb;
	size_t			i;

	while (ft_isspace(*nptr))
		++nptr;
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
