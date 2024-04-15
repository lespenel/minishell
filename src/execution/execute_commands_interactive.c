/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands_interactive.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 03:57:07 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 01:59:15 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "signals.h"

int	execute_commands_interactive(t_ms *ms, t_lexer *lexer)
{
	int	ret;

	setup_signals_execution();
	if (restore_termios(ms) == -1)
		return (-1);
	ret = execute_commands(ms, lexer);
	if (setup_termios(ms) == -1)
		return (-1);
	setup_signals_interactive();
	return (ret);
}
