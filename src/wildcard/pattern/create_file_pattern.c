/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_pattern.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:40:07 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 13:06:53 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_mem.h"
#include "vector.h"
#include "wildcard.h"

int	add_file_pattern(t_wildcard *wildcard, t_lexer *first_pattern, int i)
{
	t_lexer_tok	*tok;
	t_pattern	pattern;

	if (i == (int)first_pattern->size)
		return (0);
	ft_memset(&pattern, 0, sizeof(t_pattern));
	init_lexer(&pattern.pattern);
	while (i < (int)first_pattern->size)
	{
		tok = at_vector(first_pattern, i);
		if (add_vector(&pattern.pattern, tok, 1) == -1)
		{
			clear_lexer(&pattern.pattern);
			return (-1);
		}
		++i;
	}
	pattern.type = FILENAME;
	if (add_vector(&wildcard->patterns, &pattern, 1) == -1)
	{
		clear_lexer(&pattern.pattern);
		return (-1);
	}
	return (0);
}
