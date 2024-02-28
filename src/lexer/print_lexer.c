/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:43:05 by lespenel          #+#    #+#             */
/*   Updated: 2024/02/28 01:10:11 by lespenel         ###   ########.fr       */
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
	while (i < token_tab->len)
	{
		token = (t_lexer_tok *)at_vector(token_tab, i);
		if (printf("content = %s\n", token->content) == -1)
			return (-1);
		i++;
	}
	return (0);
}
