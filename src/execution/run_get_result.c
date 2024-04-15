/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_get_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 06:37:15 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 06:39:22 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "execution.h"
#include "expander.h"
#include "signals.h"
#include "builtins.h"

static int	do_builtin(t_lexer_tok *token);

int	run_get_result(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;
	pid_t		pid;
	int			ret;

	token = at_vector(lexer, i);
	pid = -1;
	if (next_token(lexer, i) == PIPE)
		pid = execute_pipeline(ms, lexer, i);
	else if (token->type == COMMAND)
	{
		ret = perform_expansions(ms, token);
		if (ret)
			return (ret);
		if (g_sig == SIGINT)
			return (130);
		if (do_builtin(token))
			return (run_builtin(ms, token));
		pid = execute_simple_command(ms, lexer, i);
	}
	else if (token->type == SUBSHELL)
		pid = execute_subshell(ms, lexer, i);
	return (wait_children(ms, pid));
}

static int	do_builtin(t_lexer_tok *token)
{
	char		**s;

	if (token->args.size != 0)
	{
		s = at_vector(&token->args, 0);
		if (s != NULL && is_builtin(*s))
			return (1);
	}
	return (0);
}
