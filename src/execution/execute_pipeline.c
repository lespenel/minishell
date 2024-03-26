/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 05:04:03 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/26 06:28:53 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "execution.h"
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

static int	is_next_pipe(t_lexer *lexer, size_t i);
static int	execute_pipe_cmd(t_ms *ms, t_lexer_tok *token, int fdin, int last);

int	execute_pipeline(t_ms *ms, t_lexer *lexer, size_t i)
{
	(void)ms;
	int	fd;
	t_lexer_tok	*token;

	fd = -1;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == LOGICAL_OR || token->type == LOGICAL_AND)
			break;
		else if (token->type == COMMAND || token->type == SUBSHELL)
		{
			fd = execute_pipe_cmd(ms, token, fd, is_next_pipe(lexer, i) == 0);
			if (fd == -1)
				return (-1);
		}
		++i;
	}
	wait(NULL);
	wait(NULL);
	return (0);
}

static int	execute_pipe_cmd(t_ms *ms, t_lexer_tok *token, int fdin, int last)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	if (fork() == 0)
	{
		close(fd[0]);
		if (fdin != -1)
		{
			if (dup2(fdin, STDIN_FILENO) == -1)
				exit(-1);
			close(fdin);
		}
		if (last == 0)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit(-1);
			close(fd[1]);
		}
		execute_command(ms, token);
	}
	close(fdin);
	close(fd[1]);
	return (fd[0]);
}

static int	is_next_pipe(t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;

	++i;
	if (i < lexer->size)
	{
		token = at_vector(lexer, i);
		return (token->type == PIPE);
	}
	return (0);
}
