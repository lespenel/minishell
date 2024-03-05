/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/04 13:30:38 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
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

	(void)argc;
	(void)argv;
	if (init_minishell(&minishell, envp) == -1)
		return (1);
	print_env(&minishell.env);
	ms_setenv(&minishell.env, "PATH", "/");
	printf("\n\n\n");
	print_env(&minishell.env);
	str = readline(prompt);
	while (str)
	{
		free(str);
		str = readline(prompt);
		if (str == NULL)
			break ;
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
