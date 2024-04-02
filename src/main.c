/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/02 12:48:07 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "lexer.h"
#include "signals.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

static int	init_minishell(t_ms *ms, char *envp[]);
static void	destroy_minishell(t_ms *ms);

void	signal_sigquit(int sig)
{
	(void)sig;
}

int	main(int argc, char **argv, char *envp[])
{
	t_ms		ms;
	char		*input;
	t_lexer		lexer;

	(void)argc;
	(void)argv;
	if (init_minishell(&ms, envp) == -1)
		return (-1);
	input = readline(PROMPT);
	while (input)
	{
		if (parse_input(&ms, &lexer, input) == -1)
			return (-1);
		clear_lexer(&lexer);
		add_history(input);
		free(input);
		input = readline(PROMPT);
	}
	rl_clear_history();
	destroy_minishell(&ms);
	return (0);
}

static int	init_minishell(t_ms *ms, char *envp[])
{
	if (init_env(&ms->env, envp) == -1)
		return (-1);
	setup_signals_interactive();
	ms->lastexit = 0;
	return (0);
}

static void	destroy_minishell(t_ms *ms)
{
	destroy_env(&ms->env);
}
