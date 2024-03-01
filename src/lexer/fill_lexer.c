/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/01 07:25:09 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

static int	add_word_tok(t_lexer *lexer, char *s, size_t *index);
static int	add_operator_tok(t_lexer *lexer, char *s);
static int	add_quoted_word_tok(t_lexer *lexer, char *s, size_t n);

int	fill_lexer(t_lexer *lexer, char *s)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			j = to_next_quote(s + i);
			printf("j = %ld\n", j);
			if (j == 0)
				return (printf("Erreur de quote\n"));
			if (add_quoted_word_tok(lexer, s + i + 1, j) == -1)
				return (-1);
			i += j + 1;
		}
		else if (is_word(s[i]))
		{
			if (add_word_tok(lexer, s + i, &i) == -1)
				return (-1);
		}
		else if (is_operand(s[i]))
		{
			if (add_operator_tok(lexer, s + i) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

static int	add_quoted_word_tok(t_lexer *lexer, char *s, size_t n)
{
	t_lexer_tok	token;

	token.content = malloc(sizeof(char) * n + 1);
	if (token.content == NULL)
		return (-1);
	ft_strncpy(token.content, s, n - 1);
	token.content[n - 1] = '\0';
	if (s[n - 1] == '\'')
		token.type = WORD_SQUOTED;
	else
		token.type = WORD_DQUOTED;
	if (add_vector(lexer, &token, 1) == -1)
		return (-1);
	return (0);
}

static int	add_word_tok(t_lexer *lexer, char *s, size_t *index)
{
	size_t		j;
	t_lexer_tok	token;

	j = 0;
	while (s[j] && is_word(s[j]))
		j++;
	if (j != 0)
	{
		token.content = malloc(sizeof(char) * (j + 1));
		if (token.content == NULL)
			return (-1);
		ft_strncpy(token.content, s, j);
		token.content[j] = '\0';
		token.type = WORD;
		if (add_vector(lexer, &token, 1) == -1)
			return (-1);
		*index += j - 1;
	}
	return (0);
}

static int	add_operator_tok(t_lexer *lexer, char *s)
{
	t_lexer_tok	token;

	if (is_operand(*s))
	{
		token.content = malloc(sizeof(char) * 2);
		if (token.content == NULL)
			return (-1);
		ft_strncpy(token.content, s, 1);
		token.content[1] = '\0';
		token.type = OPERAND;
		if (add_vector(lexer, &token, 1) == -1)
			return (-1);
	}
	return (0);
}
