/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/14 12:13:31 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static int	init_minishell(t_minishell *minishell, char *envp[]);
static void	destroy_minishell(t_minishell *minishell);

int	main(int argc, char **argv, char *envp[])
{
	t_minishell	minishell;
	char		*str;
	t_lexer		lexer;

	(void)argc;
	(void)argv;
	if (init_minishell(&minishell, envp) == -1)
		return (-1);
	str = malloc(0);
	while (str)
	{
		free(str);
		str = readline(PROMPT);
		if (str == NULL)
			break ;
		if (parse_input(&minishell.env, &lexer, str) == -1)
			return (-1);
		add_history(str);
		print_lexer(&lexer);
		clear_lexer(&lexer);
	}
	rl_clear_history();
	clear_lexer(&lexer);
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
