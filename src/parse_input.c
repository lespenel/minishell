/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:17:56 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/28 02:29:53 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "execution.h"

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
