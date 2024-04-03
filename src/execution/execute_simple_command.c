/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:46:44 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/03 13:31:22 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "execution.h"
#include "vector.h"
#include <stdlib.h>
#include <unistd.h>

int	execute_single_command(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	token;
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		clear_lexer_except(lexer, i, &token);
		exit(run_command(ms, &token));
	}
	return (pid);
}
