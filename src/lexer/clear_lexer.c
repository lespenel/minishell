/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:39:25 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 23:27:02 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include <stddef.h>
#include <stdlib.h>

int	clear_lexer(t_lexer *token_tab)
{
	size_t		i;

	i = 0;
	if (token_tab == NULL)
		return (-1);
	while (i < token_tab->size)
	{
		clear_token(at_vector(token_tab, i));
		i++;
	}
	free(token_tab->array);
	token_tab->array = NULL;
	token_tab->size = 0;
	token_tab->elemsize = 0;
	token_tab->allocated = 0;
	return (0);
}
