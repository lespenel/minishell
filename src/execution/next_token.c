/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 07:30:10 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/27 07:30:41 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lex_type	next_token(t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;

	++i;
	if (i >= lexer->size)
		return (-1);
	token = at_vector(lexer, i);
	return (token->type);
}
