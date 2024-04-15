/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/15 03:03:53 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include "ft_io.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <termios.h>

int	g_sig = 0;

int	main(int argc, char **argv, char *envp[])
{
	t_ms		ms;

	(void)argc;
	(void)argv;
	if (init_minishell(&ms, envp) == -1)
	{
		destroy_minishell(&ms);
		return (-1);
	}
	if (run_shell(&ms) == -1)
	{
		rl_clear_history();
		destroy_minishell(&ms);
		return (-1);
	}
	rl_clear_history();
	destroy_minishell(&ms);
	ft_dprintf(STDERR_FILENO, "exit\n");
	return (ms.lastexit);
}
