/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/20 01:20:59 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "lexer.h"
#include "lexer.h"
#include "expander.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static int	init_minishell(t_ms *ms, char *envp[]);
static void	destroy_minishell(t_ms *ms);

int	main(int argc, char **argv, char *envp[])
{
	const char	*prompt = "minishell $> ";
	t_ms		ms;
	char		*str;
	t_lexer		lexer;

	(void)argc;
	(void)argv;
	if (init_minishell(&ms, envp) == -1)
		return (1);
	str = readline(prompt);
	while (str)
	{
		init_lexer(&lexer);
		fill_lexer(&lexer, str);
		print_lexer(&lexer);
		expand_tokens(&ms, &lexer);
		dprintf(2, "\nEXPANDED : \n\n");
		print_lexer(&lexer);
		free(str);
		clear_lexer(&lexer);
		str = readline(prompt);
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
