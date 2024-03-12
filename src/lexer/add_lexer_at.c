/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexer_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:09:05 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/12 01:24:45 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "lexer.h"

int	add_lexer_at(t_lexer *lexer, t_lexer *new_lex, size_t index)
{
	t_lexer *token;
	size_t	i;

	i = 0;
	remove_vector(lexer, index);
	while (i < new_lex->size)
	{
		token = at_vector(new_lex, i);
		if (add_vector_at(lexer, token, index + i) == -1)
			return (-1);
		++i;
	}
	return (0);
}
