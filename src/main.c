/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/18 05:16:25 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "lexer.h"
#include "builtins.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static int	init_minishell(t_minishell *minishell, char *envp[]);
static void	destroy_minishell(t_minishell *minishell);

int	main(int argc, char **argv, char *envp[])
{
	t_minishell	minishell;
	t_lexer		lexer;
	char		*input;

	(void)argc;
	(void)argv;
	if (init_minishell(&minishell, envp) == -1)
		return (-1);
	input = malloc(0);
	while (input)
	{
		free(input);
		input = readline(PROMPT);
		if (input == NULL)
			break ;
		if (parse_input(&minishell.env, &lexer, input) == -1)
			return (-1);
		if (exec_test(&minishell, &lexer) == -1)
			return (-1);
		add_history(input);
		print_lexer(&lexer);
		clear_lexer(&lexer);
	}
	rl_clear_history();
	destroy_minishell(&minishell);
	return (0);
}

static int	init_minishell(t_minishell *minishell, char *envp[])
{
	if (init_env(&minishell->env, envp) == -1)
		return (-1);
	return (0);
}

static void	destroy_minishell(t_minishell *minishell)
{
	destroy_env(&minishell->env);
}
