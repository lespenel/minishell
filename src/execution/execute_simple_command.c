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
#include "signals.h"
#include "util.h"
#include <stdlib.h>
#include <unistd.h>

int	execute_single_command(t_ms *ms, t_lexer *lexer, size_t i)
{
	pid_t		pid;

	pid = ms_fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_signals_child();
		exit(run_command(ms, lexer, i));
	}
	return (pid);
}
