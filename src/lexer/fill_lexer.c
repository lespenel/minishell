/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/02/29 20:05:55 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

static int	add_word_tok(t_lexer *token_tab, char *str_usr, size_t *index);
static int	add_operator_tok(t_lexer *token_tab, char *str_usr);
//static int		add_quoted_word_tok(t_lexer *token_tab, char *str_usr, size_t n);

int	fill_lexer(t_lexer *token_tab, char *str_usr)
{
	size_t		i;
//	size_t		j;

	i = 0;
	while (str_usr[i])
	{
		/*
		if (is_quote(str_usr + i))
		{
			j = 0;
			while (is_quote(str_usr + i + j))
				j++;
			add_quoted_word_tok(token_tab, str_usr, j);
			i += j + 1;
		}*/
		if (add_word_tok(token_tab, str_usr + i, &i) == -1)
			return (-1);
		if (add_operator_tok(token_tab, str_usr + i))
			return (-1);
		else
			i++;
	}
	return (0);
}

/*
static int		add_quoted_word_tok(t_lexer *token_tab, char *str_usr, size_t n)
{
	t_lexer_tok	token;

	token.content = malloc(sizeof(char) * n + 1);
	if (token.content == NULL)
		return (-1);
	ft_strlcpy(token.content, str_usr, n + 1);
	token.type = WORD;
	if (add_vector(token_tab, &token, 1) == -1)
			return (-1);
	return (0);
}*/

static int	add_word_tok(t_lexer *token_tab, char *str_usr, size_t *index)
{
	size_t		j;
	t_lexer_tok	token;

	j = 0;
	while (str_usr[j] && is_word(str_usr[j]))
		j++;
	if (j != 0)
	{
		token.content = malloc(sizeof(char) * j + 1);
		if (token.content == NULL)
			return (-1);
		ft_strlcpy(token.content, str_usr, j + 1);
		token.type = WORD;
		if (add_vector(token_tab, &token, 1) == -1)
			return (-1);
		*index += j - 1;
	}
	return (0);
}

static int	add_operator_tok(t_lexer *token_tab, char *str_usr)
{
	t_lexer_tok	token;

	if (is_operand(*str_usr))
	{
		token.content = malloc(sizeof(char) * 2);
		if (token.content == NULL)
			return (-1);
		ft_strlcpy(token.content, str_usr, 2);
		token.type = OPERAND;
		if (add_vector(token_tab, &token, 1) == -1)
			return (-1);
	}
	return (0);
}
