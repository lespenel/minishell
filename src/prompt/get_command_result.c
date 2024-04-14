/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_result.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:20:56 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/14 17:18:45 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "vector.h"
#include "ft_string.h"
#include "ft_io.h"
#include "execution.h"
#include "env.h"
#include "util.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	get_child_result(t_ms *ms, char **argv, int pfd[2]);
static char	*read_result(pid_t pid, int pfd[2]);
static int	fill_result_vector(t_vector *vector, int pfd[2]);

char	*get_command_result(t_ms *ms, char **argv)
{
	int			pfd[2];
	pid_t		pid;
	int			ret;

	if (pipe(pfd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
	{
		close(pfd[0]);
		close(pfd[1]);
		return (NULL);
	}
	if (pid == 0)
	{
		ret = get_child_result(ms, argv, pfd);
		if (ret == -1)
		{
			destroy_minishell(ms);
			exit(1);
		}
		exit(ret);
	}
	return (read_result(pid, pfd));
}

static int	get_child_result(t_ms *ms, char **argv, int pfd[2])
{
	char	**envp;
	char	*path;

	if (close(pfd[0]) == -1)
	{
		close(pfd[1]);
		return (-1);
	}
	if (dup_and_close(pfd[1], STDOUT_FILENO) == -1
		|| close(STDERR_FILENO) == -1)
		return (-1);
	path = argv[0];
	if (ft_strchr(path, '/') == NULL)
		path = get_path(ms, argv[0]);
	if (path == NULL)
	{
		destroy_minishell(ms);
		return (127);
	}
	envp = get_envp(&ms->env);
	if (envp == NULL)
		return (-1);
	destroy_minishell(ms);
	execve(path, argv, envp);
	return (126);
}

static char	*read_result(pid_t pid, int pfd[2])
{
	t_vector	result;

	init_vector(&result, sizeof(char));
	if (fill_result_vector(&result, pfd) == -1)
	{
		close(pfd[STDIN_FILENO]);
		kill(pid, SIGKILL);
		wait(NULL);
		clear_vector(&result);
		return (NULL);
	}
	if (wait(NULL) == -1)
	{
		close(pfd[0]);
		clear_vector(&result);
		return (NULL);
	}
	if (close(pfd[0]) == -1)
	{
		clear_vector(&result);
		return (NULL);
	}
	return (result.array);
}

static int	fill_result_vector(t_vector *vector, int pfd[2])
{
	char		*line;

	if (close(pfd[1]) == -1)
		return (-1);
	if (add_vector(vector, "", 0) == -1)
		return (-1);
	errno = 0;
	line = get_next_line(pfd[0]);
	while (line)
	{
		if (add_vector(vector, line, ft_strlen(line)) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
		line = get_next_line(pfd[0]);
	}
	return ((errno == 0) - 1);
}
