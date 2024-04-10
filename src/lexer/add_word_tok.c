/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:09:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/10 07:13:35 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "ft_string.h"
#include "lexer.h"
#include <stdlib.h>

static ssize_t	get_word_size(char *s);

ssize_t	add_word_tok(t_lexer *lexer, char *s)
{
	ssize_t		i;
	t_lexer_tok	token;

	i = get_word_size(s);
	if (i == -1)
		return (0);
	if (i > 0)
	{
		token.content = malloc(sizeof(char) * (i + 1));
		if (token.content == NULL)
			return (-1);
		ft_strncpy(token.content, s, i);
		token.content[i] = '\0';
		token.type = WORD;
		if (add_vector(lexer, &token, 1) == -1)
			return (-1);
	}
	return (i);
}

static ssize_t	get_word_size(char *s)
{
	size_t		i;
	ssize_t		j;
	ssize_t		ret;

	i = next_char(s, -1);
	while (s[i] && is_word(s[i]))
	{
		if (is_quote(s[i]))
		{
			ret = to_next_quote(s + i);
			if (ret == 0)
				return (-1);
			i += ret;
		}
		i = next_char(s, i);
	}
	if (i > 0 && s[i - 1] == '\\')
	{
		j = i - 1;
		while (j >= 0 && s[j] == '\\')
			--j;
		if ((i - 1 - j) % 2)
			return (-1);
	}
	return (i);
}
