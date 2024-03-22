/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:43:05 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/22 02:26:54 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stddef.h>
#include <stdio.h>

static void	print_subshell(t_lexer_tok *token);

int	print_lexer(t_lexer *token_tab)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	printf("\n");
	while (i < token_tab->size)
	{
		token = at_vector(token_tab, i);
		if (token->type == SUBSHELL)
			print_subshell(token);
		else if (printf("content = %-10s | token = %d\n",
				token->content, token->type) == -1)
			return (-1);
		i++;
	}
	printf("\n");
	return (0);
}

static void	print_subshell(t_lexer_tok *token)
{
	printf("ENTER  SUBSHELL !!\n");
	print_lexer(&token->subshell);
	printf("EXIT  SUBSHELL !!\n");
}
