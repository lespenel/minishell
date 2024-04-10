/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_result.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:20:56 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/10 08:31:00 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "vector.h"
#include "ft_string.h"
#include "ft_io.h"
#include "execution.h"
#include "env.h"
#include <stdlib.h>
#include <unistd.h>

static int kaboul(t_ms *ms, char **argv);

char	*get_command_result(t_ms *ms, char **argv)
{
	int			pfd[2];
	t_vector	result;
	char		*line;

	if (pipe(pfd) == -1)
		return (NULL);
	if (fork() == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		close(2);
		exit(kaboul(ms, argv));
	}
	close(pfd[1]);
	init_vector(&result, sizeof(char));
	add_vector(&result, "", 0);
	line = get_next_line(pfd[0]);
	while (line)
	{
		add_vector(&result, line, ft_strlen(line));
		line = get_next_line(pfd[0]);
	}
	close(pfd[0]);
	wait(NULL);
	return (result.array);
}

static int kaboul(t_ms *ms, char **argv)
{
	char	**envp;
	char	*path;

	path = argv[0];
	if (ft_strchr(path, '/') == NULL)
		path = get_path(ms, argv[0]);
	if (path == NULL)
		return (127);
	envp = get_envp(&ms->env);
	if (envp == NULL)
		return (-1);
	execve(path, argv, envp);
	return (126);
}
