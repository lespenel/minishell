/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/15 01:20:50 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <errno.h>
#include <stdio.h>
#include <readline/history.h>

static int	add_tokens(t_lexer *lexer, char *s, size_t i);

int	fill_lexer(t_lexer *lexer, char *s)
{
	size_t		i;
	int			ret;

	i = 0;
	ret = 0;
	errno = 0;
	while (s[i])
	{
		ret = add_tokens(lexer, s, i);
		i += ret;
		if (ret == 0)
		{
			clear_lexer(lexer);
			init_lexer(lexer);
			return (refill_lexer(lexer, s));
		}
		else if (ret == -1)
			return (-1);
	}
	add_history(s);
	return (add_newline_tok(lexer));
}

static int	add_tokens(t_lexer *lexer, char *s, size_t i)
{
	int	ret;

	ret = 0;
	if (is_word(s + i))
		ret = add_word_tok(lexer, s + i);
	else if (is_operand(s[i]))
		ret = add_operand_tok(lexer, s + i);
	else
		ret = 1;
	return (ret);
}
