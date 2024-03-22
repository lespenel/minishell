/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:17:56 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/22 02:17:33 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "wildcard.h"
#include "minishell.h"
#include "expander.h"
#include "execution.h"
#include "quote_removal.h"

int	parse_input(t_ms *ms, t_lexer *lexer, char *input)
{
	int	ret;
(void)ms;
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
	print_lexer(lexer);
	if (execution_structure(lexer) == -1)
		return (clear_lexer(lexer));
	/*if (expand_tokens(ms, lexer) == -1)
		return (-1);
	print_lexer(lexer);
	if (expand_wildcards(&ms->env, lexer) == -1)
		return (-1);
	if (quote_removal(lexer) == -1)
		return (-1);*/
	return (0);
}
