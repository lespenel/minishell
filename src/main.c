/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:52:26 by lespenel          #+#    #+#             */
/*   Updated: 2024/02/28 00:19:05 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	const char	*prompt = "minishell $> ";
	char		*str;

	(void)argc;
	(void)argv;
	(void)envp;
	str = readline(prompt);
	if (str == NULL)
		return (1);
	while (str)
	{
		free(str);
		str = readline(prompt);
	}
	rl_clear_history();
	return (0);
}
