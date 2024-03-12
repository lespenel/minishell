/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexer_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:09:05 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/12 09:20:18 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "vector.h"
#include "lexer.h"
#include "ft_mem.h"
#include "vector.h"
#include <stdlib.h>

int	add_lexer_at(t_lexer *lexer, t_lexer *new_lex, size_t index)
{
	t_lexer_tok	*token;
	t_lexer_tok	new_token;
	size_t		i;

	i = 0;
	token = at_vector(lexer, index);
	free(token->content);
	remove_vector(lexer, index);
	while (i < new_lex->size)
	{
		token = at_vector(new_lex, i);
		new_token.content = ft_strdup(token->content);
		if (new_token.content == NULL)
			return (-1);
		new_token.type = WORD;
		if (add_vector_at(lexer, &new_token, index + i) == -1)
			return (-1);
		++i;
	}
	return (0);
}
