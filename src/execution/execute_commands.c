/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:20:04 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/06 23:05:36 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "lexer.h"
#include "vector.h"
#include "execution.h"
#include "util.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

static int		end_shell(t_lexer *lexer, size_t i, int exitcode);
static int		run_get_result(t_ms *ms, t_lexer *lexer, size_t i);
static size_t	next_command(t_lexer *lexer, size_t i);

int	execute_commands(t_ms *ms, t_lexer *lexer)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == COMMAND || token->type == SUBSHELL)
		{
			ms->lastexit = run_get_result(ms, lexer, i);
			if (ms->lastexit == -1)
				return (-1);
			if (set_exitcode_str(ms, ms->lastexit) == -1)
				return (-1);
		}
		i = next_command(lexer, i);
		if (end_shell(lexer, i, ms->lastexit))
			break ;
		++i;
	}
	return (ms->lastexit);
}

static int	end_shell(t_lexer *lexer, size_t i, int exitcode)
{
	t_lexer_tok	*token;

	if (exitcode == -1)
		return (1);
	if (i >= lexer->size)
		return (0);
	token = at_vector(lexer, i);
	return ((token->type == LOGICAL_AND && exitcode != 0)
		|| (token->type == LOGICAL_OR && exitcode == 0));
}

static int	run_get_result(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;
	pid_t		pid;
	char		**s;

	token = at_vector(lexer, i);
	pid = -1;
	if (next_token(lexer, i) == PIPE)
		pid = execute_pipeline(ms, lexer, i);
	else if (token->type == COMMAND)
	{
		s = at_vector(&token->args, 0);
		if (s != NULL && is_builtin(*s))
			return (run_builtin(ms, token));
		pid = execute_single_command(ms, lexer, i);
	}
	else if (token->type == SUBSHELL)
		pid = execute_subshell(ms, lexer, i);
	if (pid == -1)
		return (-1);
	return (wait_children(pid));
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
