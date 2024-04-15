/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_lexer_unlink.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 05:52:30 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 06:00:11 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int	clear_lexer_unlink(t_lexer *token_tab)
{
	size_t		i;

	i = 0;
	if (token_tab == NULL)
		return (-1);
	while (i < token_tab->size)
	{
		clear_token_unlink(at_vector(token_tab, i));
		i++;
	}
	free(token_tab->array);
	token_tab->array = NULL;
	token_tab->size = 0;
	token_tab->elemsize = 0;
	token_tab->allocated = 0;
	return (0);
}
