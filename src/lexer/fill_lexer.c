/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/10 07:17:54 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include "util.h"
#include "ft_io.h"
#include <stddef.h>
#include <stdlib.h>

int	fill_lexer(t_lexer *lexer, char *s)
{
	size_t		i;
	int			ret;

	i = 0;
	ret = 0;
	init_lexer(lexer);
	while (s[i])
	{
		if (is_word(s[i]))
		{
			ret = add_word_tok(lexer, s + i);
			i += ret - 1;
		}
		else if (is_operand(s[i]))
		{
			ret = add_operand_tok(lexer, s + i);
			i += ret - 1;
		}
		if (ret == -1)
			return (-1);
		else if (ret == 0)
			return (ft_dprintf(2, SYNTAX_ERR, "&;"));
		++i;
	}
	return (add_newline_tok(lexer));
}
