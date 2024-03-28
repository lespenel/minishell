/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:20:04 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/28 04:55:28 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "vector.h"
#include "execution.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static int		end_shell(t_lexer *lexer, size_t i, int exitcode);
static int		run_and_get_result(t_ms *ms, t_lexer *lexer, size_t i);
static size_t	next_command(t_lexer *lexer, size_t i);
static int		wait_children(pid_t last);

int	execute_commands(t_ms *ms, t_lexer *lexer)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == COMMAND || token->type == SUBSHELL)
			ms->lastexit = run_and_get_result(ms, lexer, i);
		i = next_command(lexer, i);
		if (i >= lexer->size)
			return (0);
		if (end_shell(lexer, i, ms->lastexit))
			return (0);
		++i;
	}
	return (0);
}

static int	end_shell(t_lexer *lexer, size_t i, int exitcode)
{
	t_lexer_tok	*token;

	if (i >= lexer->size)
		return (0);
	token = at_vector(lexer, i);
	return ((token->type == LOGICAL_AND && exitcode != 0)
		|| (token->type == LOGICAL_OR && exitcode == 0));
}

static int	run_and_get_result(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;
	pid_t		pid;

	token = at_vector(lexer, i);
	pid = -1;
	if (next_token(lexer, i) == PIPE)
		pid = execute_pipeline(ms, lexer, i);
	else if (token->type == COMMAND)
		pid = execute_single_command(ms, lexer, i);
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

static int	wait_children(pid_t last)
{
	int		wstatus;
	pid_t	pid;
	int		ret;

	pid = 0;
	ret = -1;
	while (pid != -1)
	{
		pid = wait(&wstatus);
		if (pid == last)
		{
			if (WIFEXITED(wstatus))
				ret = WEXITSTATUS(wstatus);
			if (WIFSIGNALED(wstatus))
				ret = 128 + WTERMSIG(wstatus);
		}
	}
	if (errno != ECHILD)
		return (-1);
	return (ret);
}
