/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:11:40 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/16 15:21:26 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "builtins.h"
#include "lexer.h"
#include "vector.h"

int	exec_builtins(t_ms *minishell, t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;
	t_lexer_tok	cleartok;
	char		**args;

	token = at_vector(lexer, i);
	args = token->args.array;
	if (ft_strcmp("exit", args[0]) == 0)
	{
		clear_lexer_except(lexer, i, &cleartok);
		return (exec_builtins_cleared(minishell, &cleartok));
	}
	return (exec_builtins_cleared(minishell, token));
}
