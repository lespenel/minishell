/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:23:14 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/16 16:10:41 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "execution.h"
#include "util.h"
#include <stdlib.h>
#include <unistd.h>

int	execute_subshell(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	token;
	pid_t		pid;
	int			ret;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		clear_lexer_except(lexer, i, &token);
		ret = perform_redirections(&token);
		if (ret)
			return (ret);
		ret = execute_commands(ms, &token.subshell);
		clear_token(&token);
		destroy_minishell(ms);
		exit(ret);
	}
	return (pid);
}
