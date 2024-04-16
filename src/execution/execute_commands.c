/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:20:04 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/16 17:04:50 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "signals.h"
#include "vector.h"
#include "execution.h"
#include "util.h"
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

static int		execute_command(t_ms *ms, t_lexer *lexer, size_t i);
static int		run_cmd(t_ms *ms, t_lexer *lexer, size_t i);
static int		write_signal(t_ms *ms);
static size_t	next_command(t_lexer *lexer, size_t i);

int	execute_commands(t_ms *ms, t_lexer *lexer)
{
	size_t		i;
	int			first;

	i = 0;
	first = 1;
	while (i < lexer->size
		&& (first == 1 || (ms->signaled == 0 || ms->lastexit != 128 + SIGINT)))
	{
		if (first || run_cmd(ms, lexer, i))
		{
			if (first == 0)
				++i;
			first = 0;
			if (execute_command(ms, lexer, i) == -1)
				return (-1);
			if (write_signal(ms) == -1)
				return (-1);
		}
		else
			++i;
		i = next_command(lexer, i);
	}
	return (ms->lastexit);
}

static int	execute_command(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;

	token = at_vector(lexer, i);
	if (token->type == COMMAND || token->type == SUBSHELL)
	{
		ms->lastexit = run_get_result(ms, lexer, i);
		if (ms->lastexit == -1)
			return (-1);
		if (g_sig == SIGINT)
			ms->signaled = 1;
		if (set_exitcode_str(ms, ms->lastexit) == -1)
			return (-1);
	}
	return (0);
}

static int	run_cmd(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;

	if (ms->lastexit == -1)
		return (0);
	token = at_vector(lexer, i);
	return ((token->type == LOGICAL_AND && ms->lastexit == 0)
		|| (token->type == LOGICAL_OR && ms->lastexit != 0));
}

static int	write_signal(t_ms *ms)
{
	int	ret;

	if (ms->signaled && ms->lastexit == 128 + SIGINT)
		ret = write(STDERR_FILENO, "\n", 1);
	else if (ms->signaled && ms->lastexit == 128 + SIGQUIT)
		ret = write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	else
		return (0);
	if (ret == -1)
		return (-1);
	return (0);
}

static size_t	next_command(t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;

	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == LOGICAL_AND || token->type == LOGICAL_OR)
			return (i);
		++i;
	}
	return (i);
}
