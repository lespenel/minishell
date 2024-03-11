/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:43:05 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/11 06:14:33 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stddef.h>
#include <stdio.h>

int	print_lexer(t_lexer *token_tab)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	while (i < token_tab->size)
	{
		token = at_vector(token_tab, i);
		if (printf("content = %-10s | token = %d\n",
				token->content, token->type) == -1)
			return (-1);
		i++;
	}
	return (0);
}
