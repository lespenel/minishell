/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:23:14 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/09 07:17:12 by ccouble          ###   ########.fr       */
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
	t_lexer_tok	*token;
	pid_t		pid;

	token = at_vector(lexer, i);
	pid = ms_fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (perform_redirections(token) == -1)
			return (-1);
		exit(execute_commands(ms, &token->subshell));
	}
	return (pid);
}
