/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:01:01 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/20 01:01:46 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "vector.h"
#include "expander.h"

static int	expand_word(t_ms *minishell, t_lexer *lexer, size_t i);
static int	merge_lex(t_lexer *lexer, t_lexer *newl, t_vector *news, size_t i);

int	expand_tokens(t_ms *minishell, t_lexer *lexer)
{
	size_t		i;
	ssize_t		res;
	t_lexer_tok	*token;

	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == WORD)
		{
			res = expand_word(minishell, lexer, i);
			if (res == -1)
				return (-1);
			i += res;
		}
		else
			++i;
	}
	return (0);
}

static int	expand_word(t_ms *minishell, t_lexer *lexer, size_t i)
{
	char		*word;
	ssize_t		wlen;
	size_t		j;
	t_lexer		newlexer;
	t_vector	newstring;

	init_lexer(&newlexer);
	word = ((t_lexer_tok *)at_vector(lexer, i))->content;
	remove_vector(lexer, i);
	init_vector(&newstring, sizeof(char));
	j = 0;
	while (word[j])
	{
		wlen = expand_substr(minishell, &newlexer, &newstring, word + j);
		if (wlen == -1)
		{
			free(word);
			clear_vector(&newlexer);
			clear_vector(&newstring);
			return (-1);
		}
		j += wlen;
	}
	free(word);
	return (merge_lex(lexer, &newlexer, &newstring, i));
}

static int	merge_lex(t_lexer *lexer, t_lexer *newl, t_vector *news, size_t i)
{
	t_lexer_tok	token;
	ssize_t		res;

	if (news->size != 0)
	{
		token.type = WORD;
		token.content = news->array;
		if (add_vector(newl, &token, 1) == -1)
		{
			clear_vector(news);
			return (-1);
		}
	}
	if (merge_vector(lexer, newl, i) == -1)
	{
		clear_vector(news);
		return (-1);
	}
	res = newl->size;
	clear_vector(newl);
	return (res);
}
