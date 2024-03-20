/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/20 01:33:10 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "lexer.h"
#include "expander.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static int	init_minishell(t_ms *ms, char *envp[]);
static void	destroy_minishell(t_ms *ms);

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
		if (parse_input(&ms.env, &lexer, input) == -1)
			return (-1);
		if (expand_tokens(&ms, &lexer) == -1)
			return (-1);
		print_lexer(&lexer);
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
	return (0);
}

static void	destroy_minishell(t_ms *ms)
{
	destroy_env(&ms->env);
}
