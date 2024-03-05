/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 02:12:59 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/01 07:07:31 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"

static int	is_problem(t_lexer_tok *tok1, t_lexer_tok *tok2);

int	validate_input(t_lexer *lexer)
{
	size_t		i;

	if (lexer->size == 0)
		return (0);
	i = 0;
	while (i < lexer->size - 1)
	{
		if (is_problem(at_vector(lexer, i), at_vector(lexer, i + 1)))
			return (-1);
		++i;
	}
	return (0);
}

static int	is_problem(t_lexer_tok *tok1, t_lexer_tok *tok2)
{
	if (tok1->type == REDIRECT_IN && tok2->type != WORD)
		return (1);
	if (tok1->type == REDIRECT_OUT && tok2->type != WORD)
		return (1);
	return (0);
}
