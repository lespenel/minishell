/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 05:04:03 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/04 13:57:52 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "execution.h"
#include <asm-generic/errno-base.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

static int	is_next_pipe(t_lexer *lexer, size_t i);
static int	execute_pipe_cmd(t_ms *ms, t_lexer *lexer, size_t i, int fdin);
static int	execute_last_cmd(t_ms *ms, t_lexer *lexer, size_t i, int fdin);

int	execute_pipeline(t_ms *ms, t_lexer *lexer, size_t i)
{
	int			fd;
	pid_t		pid;

	fd = -1;
	while (is_next_pipe(lexer, i))
	{
		fd = execute_pipe_cmd(ms, lexer, i, fd);
		if (fd == -1)
			return (-1);
		i += 2;
	}
	pid = execute_last_cmd(ms, lexer, i, fd);
	return (pid);
}

static int	execute_pipe_cmd(t_ms *ms, t_lexer *lexer, size_t i, int fdin)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		close(fd[0]);
		if (fdin != -1)
		{
			if (dup2(fdin, STDIN_FILENO) == -1)
				exit(-1);
			close(fdin);
		}
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(-1);
		close(fd[1]);
		exit(run_command(ms, lexer, i));
	}
	if (fdin != -1)
		close(fdin);
	close(fd[1]);
	return (fd[0]);
}

static int	execute_last_cmd(t_ms *ms, t_lexer *lexer, size_t i, int fdin)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (fdin != -1)
		{
			if (dup2(fdin, STDIN_FILENO) == -1)
				exit(-1);
			close(fdin);
		}
		exit(run_command(ms, lexer, i));
	}
	close(fdin);
	return (pid);
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
