/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 00:30:59 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/17 04:33:37 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "builtins.h"
#include "vector.h"
#include <stdio.h>

int	exec_test(t_minishell *minishell, t_lexer *lexer)
{
	t_lexer_tok	*token;
	size_t		i;
	char		**args;

	i = 0;
	while (i < lexer->size - 1)
	{
		token = at_vector(lexer, i);
		if (token->type == WORD)
		{
			args = get_args(lexer, i);
			if (args == NULL)
				return (-1);
			if (is_builtin(token->content))
			{
				if (exec_builtins(minishell, args, token->content) == -1)
					return (-1);
			}
			else
				dprintf(2, CMD_NOT_FOUND, args[0]);
			while (token->type == WORD)
			{
				++i;
				token = at_vector(lexer, i);
			}
		}
		++i;
	}
	return (0);
}
