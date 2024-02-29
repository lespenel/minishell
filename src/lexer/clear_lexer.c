/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:39:25 by lespenel          #+#    #+#             */
/*   Updated: 2024/02/29 20:05:11 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include <stddef.h>
#include <stdlib.h>

int	clear_lexer(t_lexer *token_tab)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	if (token_tab == NULL)
		return (-1);
	while (i < token_tab->size)
	{
		token = (t_lexer_tok *)at_vector(token_tab, i);
		if (token->content)
		{
			free(token->content);
			token->type = 0;
		}
		i++;
	}
	free(token_tab->array);
	token_tab->array = NULL;
	token_tab->size = 0;
	token_tab->elemsize = 0;
	token_tab->allocated = 0;
	return (0);
}
