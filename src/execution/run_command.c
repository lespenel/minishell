/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:14:46 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/07 05:19:21 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"
#include "expander.h"
#include "lexer.h"
#include "execution.h"
#include "ft_string.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	get_result(t_ms *ms, t_lexer_tok *token);
static int	end_cmd(t_ms *ms, t_lexer_tok *token, char *path);

int	run_command(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	token;
	int			ret;

	clear_lexer_except(lexer, i, &token);
	ret = get_result(ms, &token);
	clear_token(&token);
	destroy_minishell(ms);
	return (ret);
}

static int	get_result(t_ms *ms, t_lexer_tok *token)
{
	char	*path;
	int		ret;

	if (perform_expansions(ms, token) == -1)
		return (-1);
	ret = perform_redirections(token);
	if (ret == -1)
		return (-1);
	if (ret == 1)
		return (1);
	if (token->type == SUBSHELL)
		return (execute_commands(ms, &token->subshell));
	if (token->args.size == 0)
		return (0);
	path = *((char **)at_vector(&token->args, 0));
	if (is_builtin(path))
		return (exec_builtins(ms, NULL, token->args.array));
	return (end_cmd(ms, token, path));
}

static int	end_cmd(t_ms *ms, t_lexer_tok *token, char *path)
{
	char	**envp;

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
	execve(path, token->args.array, envp);
	return (126);
}
