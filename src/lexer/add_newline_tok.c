/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_newline_tok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:11:05 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/12 00:11:05 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_string.h"
#include "vector.h"

int	add_newline_tok(t_lexer *lexer)
{
	t_lexer_tok	token;

	token.content = ft_strdup("newline");
	if (token.content == NULL)
		return (-1);
	token.type = NEWLINE;
	if (add_vector(lexer, &token, 1) == -1)
		return (-1);
	return (0);
}
