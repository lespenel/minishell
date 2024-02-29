/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/02/28 23:54:37 by lespenel         ###   ########.fr       */
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
	t_lexer		token_tab;

	(void)argc;
	(void)argv;
	(void)envp;
	init_lexer(&token_tab);
	str = readline(prompt);
	if (str == NULL)
		return (1);
	while (str)
	{
		init_lexer(&token_tab);
		if (fill_lexer(&token_tab, str) == -1)
			return (printf("Error lexer\n"));
		print_lexer(&token_tab);
		clear_lexer(&token_tab);
		free(str);
		str = readline(prompt);
	}
	rl_clear_history();
	return (0);
}
