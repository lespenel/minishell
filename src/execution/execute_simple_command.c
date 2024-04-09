/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:46:44 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/09 07:18:51 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "execution.h"
#include "minishell.h"
#include "vector.h"
#include "execution.h"
#include "ft_string.h"
#include <stdio.h>
#include "signals.h"
#include "util.h"
#include <stdlib.h>
#include <unistd.h>

static int	simple_cmd_exec(t_ms *ms, t_lexer_tok *token);

int	execute_simple_command(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	token;
	pid_t		pid;
	int			ret;

	pid = ms_fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		clear_lexer_except(lexer, i, &token);
		ret = simple_cmd_exec(ms, &token);
		clear_token(&token);
		destroy_minishell(ms);
		exit(ret);
	}
	return (pid);
}

static int	simple_cmd_exec(t_ms *ms, t_lexer_tok *token)
{
	char	*path;
	int		ret;

	ret = perform_redirections(token);
	if (ret == -1)
		return (-1);
	if (ret == 1)
		return (1);
	if (token->args.size == 0)
		return (0);
	path = *((char **)at_vector(&token->args, 0));
	return (exec_cmd(ms, token, path));
}
