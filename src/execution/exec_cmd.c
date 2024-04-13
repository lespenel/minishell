/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 06:06:57 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/10 05:18:36 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "minishell.h"
#include "ft_io.h"
#include "execution.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

static int	is_directory(char *path);

int	exec_cmd(t_ms *ms, t_lexer_tok *token, char *path)
{
	char	**envp;

	if (ft_strchr(path, '/') == NULL)
		path = get_path(ms, *((char **)at_vector(&token->args, 0)));
	if (path == NULL)
	{
		ft_dprintf(2, "%s: command not found\n",
			*((char **)at_vector(&token->args, 0)));
		return (127);
	}
	envp = get_envp(&ms->env);
	if (envp == NULL)
		return (-1);
	if (is_directory(path))
	{
		ft_dprintf(2, "minishell: %s: %s\n", path, strerror(EISDIR));
		return (126);
	}
	execve(path, token->args.array, envp);
	ft_dprintf(2, "minishell: %s: %s\n", path, strerror(errno));
	return (126);
}

static int	is_directory(char *path)
{
	struct stat	buff;
	int			ret;

	if (stat(path, &buff) < 0)
		ret = 0;
	else
		ret = S_ISDIR(buff.st_mode);
	return (ret);
}
