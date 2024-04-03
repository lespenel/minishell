/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:14:46 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/02 13:53:25 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"
#include "expander.h"
#include "lexer.h"
#include "execution.h"
#include "ft_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	run_command(t_ms *ms, t_lexer_tok *token)
{
	char	**envp;
	char	*path;

	if (perform_expansions(ms, token) == -1)
		return (-1);
	if (perform_redirections(token) == -1)
		return (-1);
	if (token->type == SUBSHELL)
		return (execute_commands(ms, &token->subshell));
	if (token->args.size == 0)
		return (0);
	path = *((char **)at_vector(&token->args, 0));
	if (is_builtin(path))
		return (exec_builtins(ms, NULL, token->args.array));
	else
	{
		if (ft_strchr(path, '/') == NULL)
			path = get_path(ms, *((char **)at_vector(&token->args, 0)));
		if (path == NULL)
		{
			dprintf(2, "%s: command not found\n",
			   *((char **)at_vector(&token->args, 0)));
			return (127);
		}
		envp = get_envp(&ms->env);
		if (envp == NULL)
			return (-1);
	}
	execve(path, token->args.array, envp);
	return (126);
}
