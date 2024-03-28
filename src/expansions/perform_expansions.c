/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 01:41:37 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/28 02:29:36 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lexer.h"
#include "minishell.h"

int	perform_expansions(t_ms *ms, t_lexer_tok *token)
{
	if (expand_parameters(ms, token) == -1)
		return (-1);
	if (quote_removal(token) == -1)
		return (-1);
	return (0);
}
