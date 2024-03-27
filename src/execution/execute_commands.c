/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:20:04 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/27 05:33:19 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "vector.h"
#include "ft_string.h"
#include "execution.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

static int			end_shell(t_lexer *lexer, size_t i, int exitcode);
static int			run_command(t_ms *ms, t_lexer *lexer, size_t i);
static int			execute_single_command(t_ms *ms, t_lexer *lexer, size_t i);
static t_lex_type	next_operator(t_lexer *lexer, size_t i);
static size_t		next_command(t_lexer *lexer, size_t i);
static int			wait_children(pid_t last);

int	execute_commands(t_ms *ms, t_lexer *lexer)
{
	size_t		i;
	t_lexer_tok	*token;
	int			exitcode;

	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == COMMAND || token->type == SUBSHELL)
		{
			exitcode = run_command(ms ,lexer, i);
			dprintf(2, "got exitcode %d\n", exitcode);
		}
		if (end_shell(lexer, i, exitcode))
			return (exitcode);
		i = next_command(lexer, i);
		if (i >= lexer->size)
			return (exitcode);
		++i;
	}
	return (exitcode);
}

static int	end_shell(t_lexer *lexer, size_t i, int exitcode)
{
	t_lexer_tok	*token;

	++i;
	if (i >= lexer->size)
		return (0);
	token = at_vector(lexer, i);
	return ((token->type == LOGICAL_AND && exitcode != 0) || (token->type == LOGICAL_OR && exitcode == 0));
}

static int	run_command(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;
	pid_t		pid;

	token = at_vector(lexer, i);
	pid = -1;
	if (next_operator(lexer, i) == PIPE)
		pid = execute_pipeline(ms, lexer, i);
	else if (token->type == COMMAND)
		pid = execute_single_command(ms, lexer, i);
	else if (token->type == SUBSHELL)
		pid = execute_subshell(ms, lexer, i);
	if (pid == -1)
		return (-1);
	return (wait_children(pid));
}

static int	execute_single_command(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;
	pid_t		pid;

	token = at_vector(lexer, i);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		execute_command(ms, token);
	return (pid);
}

static t_lex_type	next_operator(t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;

	++i;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == LOGICAL_OR || token->type == LOGICAL_AND || token->type == PIPE)
			return (token->type);
		++i;
	}
	return (-1);
}

static size_t		next_command(t_lexer *lexer, size_t i)
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
