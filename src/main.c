/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/15 00:21:58 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "hashmap.h"
#include "minishell.h"
#include "lexer.h"
#include "signals.h"
#include "util.h"
#include "ft_mem.h"
#include "prompt.h"
#include "ft_io.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

int	g_sig = 0;

static int	init_minishell(t_ms *ms, char *envp[]);
static int	run_shell(t_ms *ms);
static char	*get_line(t_ms *ms);

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
		return (-1);
	rl_clear_history();
	destroy_minishell(&ms);
	ft_dprintf(2, "exit\n");
	return (ms.lastexit);
}

static int	init_minishell(t_ms *ms, char *envp[])
{
	ft_memset(ms, 0, sizeof(t_ms));
	if (setup_termios(ms) == -1)
		return (-1);
	if (init_env(&ms->env, envp) == -1)
		return (-1);
	init_hashmap(&ms->aliases);
	setup_signals_interactive();
	ms->signaled = 0;
	if (set_exitcode_str(ms, 0) == -1)
		return (-1);
	(void)ms;
	(void)envp;
	return (0);
}

static int	run_shell(t_ms *ms)
{
	char	*input;
	t_lexer	lexer;

	input = get_line(ms);
	while (input)
	{
		if (parse_input(ms, &lexer, input) == -1)
			return (-1);
		if (g_sig == SIGINT)
		{
			if (set_exitcode_str(ms, 128 + SIGINT) == -1)
				return (-1);
			g_sig = 0;
		}
		clear_lexer(&lexer);
		free(input);
		input = get_line(ms);
	}
	return (0);
}

static char	*get_line(t_ms *ms)
{
	char	*prompt;
	char	*input;

	input = NULL;
	while (input == NULL)
	{
		prompt = get_prompt(ms);
		if (prompt == NULL)
			return (NULL);
		input = readline(prompt);
		free(prompt);
		if (g_sig == SIGINT)
		{
			if (set_exitcode_str(ms, 128 + SIGINT) == -1)
				return (NULL);
			g_sig = 0;
			free(input);
			input = NULL;
		}
		else if (input == NULL)
			return (NULL);
	}
	return (input);
}
