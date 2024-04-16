/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:14:46 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/16 15:22:42 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "expander.h"
#include "lexer.h"
#include "execution.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	get_result(t_ms *ms, t_lexer_tok *token);

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

	ret = perform_expansions(ms, token);
	if (ret)
		return (ret);
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
		return (exec_builtins_cleared(ms, token));
	return (exec_cmd(ms, token, path));
}
