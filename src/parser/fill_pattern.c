/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pattern.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 05:51:27 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/12 09:06:53 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include "wildcard.h"
#include "ft_string.h"
#include <stdlib.h>

static	ssize_t	add_quote_tok(t_lexer *pattern, char *raw_pattern);
static	ssize_t	add_word_tok(t_lexer *pattern, char *raw_pattern);
static	ssize_t	add_wildcard_tok(t_lexer *pattern, char *raw_pattern);
static	int		is_not_wildcard(char c);

int	fill_pattern(t_lexer *pattern, char *raw_pattern)
{
	ssize_t		ret;

	ret = 0;
	init_lexer(pattern);
	while (*raw_pattern)
	{
		if (*raw_pattern == '*')
		{
			ret = add_wildcard_tok(pattern, raw_pattern);
			raw_pattern += ret;
		}
		else if (is_quote(*raw_pattern))
		{
			ret = add_quote_tok(pattern, raw_pattern);
			raw_pattern += ret + 1;
		}
		else if (is_not_wildcard(*raw_pattern))
		{
			ret = add_word_tok(pattern, raw_pattern);
			raw_pattern += ret;
		}
		if (ret == -1)
			return (-1);
	}
	return (add_newline_tok(pattern));
}

static	ssize_t	add_wildcard_tok(t_lexer *pattern, char *raw_pattern)
{
	t_lexer_tok	token;
	t_lexer_tok	*before;
	ssize_t		size;

	size = 0;
	while (raw_pattern[size] == '*')
		++size;
	if (pattern->size > 0)
	{
		before = at_vector(pattern, pattern->size - 1);
		if (before->type == 0)
			return (size);
	}
	token.content = ft_strdup("*");
	if (token.content == NULL)
		return (-1);
	token.type = 0;
	if (add_vector(pattern, &token, 1) == -1)
		return (-1);
	return (size);
}

static ssize_t	add_word_tok(t_lexer *pattern, char *raw_pattern)
{
	t_lexer_tok	token;
	ssize_t		size;

	size = 0;
	while (is_not_wildcard(raw_pattern[size]))
		++size;
	token.content = malloc(sizeof(char) * size + 1);
	if (token.content == NULL)
		return (-1);
	ft_strncpy(token.content, raw_pattern, size);
	token.content[size] = 0;
	token.type = WORD;
	if (add_vector(pattern, &token, 1) == -1)
		return (-1);
	return (size);
}

static	ssize_t	add_quote_tok(t_lexer *pattern, char *raw_pattern)
{
	t_lexer_tok	token;
	ssize_t		size;

	size = to_next_quote(raw_pattern);
	if (size == 1)
		return (1);
	++raw_pattern;
	token.content = malloc(sizeof(char) * size);
	if (token.content == NULL)
		return (-1);
	ft_strncpy(token.content, raw_pattern, size - 1);
	token.content[size - 1] = 0;
	token.type = WORD;
	if (add_vector(pattern, &token, 1) == -1)
		return (-1);
	return (size);
}

static int	is_not_wildcard(char c)
{
	if (c != '*' && is_quote(c) == 0 && c > 32)
		return (1);
	return (0);
}
