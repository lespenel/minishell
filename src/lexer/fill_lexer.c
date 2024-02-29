/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/02/29 02:48:19 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int		fill_lexer(t_lexer *token_tab, char *str_usr)
{
	size_t		i;
	size_t		j;
	t_lexer_tok token;

	i = 0;

	while (str_usr[i])
	{
		j = 0;
		while (str_usr[i + j] && is_word(str_usr[i + j]))
			j++;
		if (j != 0)
		{
			token.content = malloc(sizeof(char) * j + 1);
			if (token.content == NULL)
				return (-1);
			ft_strlcpy(token.content, str_usr + i, j + 1);
			token.type = WORD;
			if (add_vector(token_tab, &token, 1) == -1)
				return (-1);
			i += j;
		}
		else
			i++;
	}
	return (0);
}
