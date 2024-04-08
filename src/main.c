/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/08 05:15:17 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "lexer.h"
#include "signals.h"
#include "util.h"
#include "ft_mem.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

int	g_sig = 0;

static int	init_minishell(t_ms *ms, char *envp[]);

int	main(int argc, char **argv, char *envp[])
{
	t_ms		ms;
	char		*input;
	t_lexer		lexer;

	(void)argc;
	(void)argv;
	if (init_minishell(&ms, envp) == -1)
	{
		destroy_minishell(&ms);
		return (-1);
	}
	input = readline(PROMPT);
	while (input)
	{
		if (g_sig == SIGINT)
		{
			if (set_exitcode_str(&ms, 128 + SIGINT) == -1)
				return (-1);
			g_sig = 0;
		}
		if (parse_input(&ms, &lexer, input) == -1)
			return (-1);
		clear_lexer(&lexer);
		add_history(input);
		free(input);
		input = readline(PROMPT);
	}
	rl_clear_history();
	destroy_minishell(&ms);
	return (ms.lastexit);
}

static int	init_minishell(t_ms *ms, char *envp[])
{
	ft_memset(ms, 0, sizeof(t_ms));
	if (setup_termios(ms) == -1)
		return (-1);
	if (init_env(&ms->env, envp) == -1)
		return (-1);
	setup_signals_interactive();
	ms->signaled = 0;
	if (set_exitcode_str(ms, 0) == -1)
		return (-1);
	return (0);
}
