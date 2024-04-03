/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_lexer_except.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:16:58 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/03 13:30:18 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

void	clear_lexer_except(t_lexer *lexer, size_t i, t_lexer_tok *token)
{
	size_t		j;

	j = 0;
	while (j < lexer->size)
	{
		if (i != j)
			clear_token(at_vector(lexer, j));
		else
			*token = *(t_lexer_tok *)at_vector(lexer, j);
		j++;
	}
	free(lexer->array);
	lexer->array = NULL;
	lexer->size = 0;
	lexer->elemsize = 0;
	lexer->allocated = 0;
}
