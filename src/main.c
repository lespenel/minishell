/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/11 08:27:29 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "wildcard.h"
#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static int	init_minishell(t_minishell *minishell, char *envp[]);
static void	destroy_minishell(t_minishell *minishell);

int	main(int argc, char **argv, char *envp[])
{
	const char	*prompt = "minishell $> ";
	t_minishell	minishell;
	char		*str;
	t_lexer		lexer;

	(void)argc;
	(void)argv;
	if (init_minishell(&minishell, envp) == -1)
		return (1);
	str = malloc(sizeof(char));
	while (str)
	{
		free(str);
		str = readline(prompt);
		if (str == NULL)
			break ;
		if (fill_lexer(&lexer, str) == -1)
			return (dprintf(2, "Lexer error\n"));
		if (validate_input(&lexer) == -1)
			return (dprintf(2, "Parser error\n"));
		print_lexer(&lexer);
		expand_wildcard(&minishell.env, &lexer);
		clear_lexer(&lexer);
		add_history(str);
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
