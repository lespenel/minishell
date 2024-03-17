/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 02:05:13 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/17 04:20:13 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/readline.h>

int	ms_exit(t_minishell *minishell, char **args)
{
	int	argc;

	argc = 0;
	while (args[argc])
		++argc;
	if (argc == 1)
	{
		clear_lexer(&minishell->lexer);
		destroy_env(&minishell->env);
		rl_clear_history();
		clear_args(args);
		exit(0);
	}
	if (write(2, "minishell: exit: too many arguments\n", 36) == -1)
		return (-1);
	return (0);
}
