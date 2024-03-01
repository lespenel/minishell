/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/01 05:41:49 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	const char	*prompt = "minishell $> ";
	char		*str;
	t_lexer		lexer;

	(void)argc;
	(void)argv;
	(void)envp;
	str = readline(prompt);
	if (str == NULL)
		return (1);
	init_lexer(&lexer);
	if (fill_lexer(&lexer, str) == -1)
		return (printf("Error lexer \n"));
	print_lexer(&lexer);
	clear_lexer(&lexer);
	while (str)
	{
		free(str);
		str = readline(prompt);
		if (str == NULL)
			break;
		init_lexer(&lexer);
		if (fill_lexer(&lexer, str) == -1)
			return (printf("Error lexer \n"));
		print_lexer(&lexer);
		clear_lexer(&lexer);
	}
	rl_clear_history();
	return (0);
}
