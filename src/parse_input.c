/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:17:56 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/25 06:47:25 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "execution.h"
#include "expander.h"
#include "wildcard.h"
#include "quote_removal.h"

int	parse_input(t_ms *ms, t_lexer *lexer, char *input)
{
	int	ret;

	ret = fill_lexer(lexer, input);
	if (ret == -1)
		return (-1);
	else if (ret)
		return (clear_lexer(lexer));
	ret = validate_input(lexer);
	if (ret == -1)
		return (-1);
	else if (ret)
		return (clear_lexer(lexer));
	if (execution_structure(lexer) == -1)
		return (clear_lexer(lexer));
	if (execute_commands(ms, lexer) == -1)
		return (-1);
	return (0);
}

// Theses expansion functions need to be rewrote
int	expansion(t_ms *ms, t_lexer *lexer)
{
	if (expand_tokens(ms, lexer) == -1)
		return (-1);
	print_lexer(lexer);
	if (expand_wildcards(&ms->env, lexer) == -1)
		return (-1);
	if (quote_removal(lexer) == -1)
		return (-1);
	return (0);
}
