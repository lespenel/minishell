/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:29:00 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/07 05:02:05 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "execution.h"
#include "util.h"
#include <stdlib.h>
#include <unistd.h>

static int	prepare_pipe(int pfd[2], int fdin);
static int	close_unused(int pfd[2], int fdin);

int	execute_pipe_cmd(t_ms *ms, t_lexer *lexer, size_t i, int fdin)
{
	int		pfd[2];
	pid_t	pid;

	if (pipe(pfd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (prepare_pipe(pfd, fdin) == -1)
		{
			clear_lexer(lexer);
			destroy_minishell(ms);
			exit(-1);
		}
		exit(run_command(ms, lexer, i));
	}
	if (close_unused(pfd, fdin) == -1)
		return (-1);
	return (pfd[0]);
}

static int	prepare_pipe(int pfd[2], int fdin)
{
	if (close(pfd[0]) == -1)
	{
		close(pfd[1]);
		close(fdin);
		return (-1);
	}
	if (fdin != -1)
	{
		if (dup_and_close(fdin, STDIN_FILENO) == -1)
		{
			close(pfd[1]);
			return (-1);
		}
	}
	if (dup_and_close(pfd[1], STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

static int	close_unused(int pfd[2], int fdin)
{
	if (fdin != -1)
	{
		if (close(fdin) == -1)
		{
			close(pfd[0]);
			close(pfd[1]);
			return (-1);
		}
	}
	if (close(pfd[1]) == -1)
	{
		close(pfd[0]);
		return (-1);
	}
	return (0);
}
