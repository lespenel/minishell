/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:17:56 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/15 03:20:52 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "signals.h"
#include <signal.h>

int	parse_input(t_ms *ms, t_lexer *lexer, char *input)
{
	int	ret;

	(void)ms;
	init_lexer(lexer);
	ret = fill_lexer(lexer, input);
	if (ret == -1)
		return (-1);
	else if (ret)
		return (1);
	if (g_sig == SIGINT)
		return (0);
	ret = validate_input(ms, lexer);
	if (ret == -1)
		return (-1);
	else if (ret)
		return (1);
	if (g_sig == SIGINT)
		return (0);
	return (0);
}
