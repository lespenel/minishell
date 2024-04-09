/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 06:06:57 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/09 06:29:11 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "minishell.h"
#include "ft_io.h"
#include "execution.h"
#include <stdio.h>
#include <unistd.h>

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
	execve(path, token->args.array, envp);
	return (126);
}
