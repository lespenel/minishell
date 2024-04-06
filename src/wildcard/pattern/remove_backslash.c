/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:31:56 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/05 16:39:44 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include "wildcard.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

static int	get_new_word(t_lexer_tok *tok);
static char	*ft_strncpy_no_backslash(char *dest, const char *src, size_t n);

int	remove_backslash(t_lexer *pattern)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	while (i < pattern->size)
	{
		token = at_vector(pattern, i);
		if (token->type == WORD)
		{
			if (get_new_word(token) == -1)
				return (-1);
		}
		++i;
	}
	return (0);
}

static int	get_new_word(t_lexer_tok *tok)
{
	size_t	new_len;
	size_t	len;
	char	*str;

	new_len = ft_strlen(tok->content);
	len = 0;
	while (tok->content[len])
	{
		if (tok->content[len] == '\\')
		{
			++len;
			--new_len;
		}
		++len;
	}
	str = malloc(sizeof(char) * (new_len + 1));
	if (str == NULL)
		return (-1);
	ft_strncpy_no_backslash(str, tok->content, new_len + 1);
	free(tok->content);
	tok->content = str;
	return (0);
}

static char	*ft_strncpy_no_backslash(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n - 1)
	{
		if (src[i] == '\\')
			++src;
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		++i;
	}
	return (dest);
}
