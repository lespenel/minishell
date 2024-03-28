/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/28 10:33:55 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include "util.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

static int		add_operand_token(t_lexer *lexer, char *s);
static int		get_operand_token(const char *operand_type[], char *s);
static ssize_t	add_word_tok(t_lexer *lexer, char *s);
static ssize_t	get_word_size(char *s);

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
			ret = add_operand_token(lexer, s + i);
			i += ret - 1;
		}
		if (ret == -1)
			return (-1);
		else if (ret == 0)
			return (dprintf(2, SYNTAX_ERR, "\"';&"));
		++i;
	}
	return (add_newline_tok(lexer));
}

static ssize_t	add_word_tok(t_lexer *lexer, char *s)
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

static int	add_operand_token(t_lexer *lexer, char *s)
{
	static const char	*operand_type[] = {
	[LOGICAL_OR] = "||",
	[LOGICAL_AND] = "&&",
	[APPEND] = ">>",
	[HERE_DOC] = "<<",
	[PIPE] = "|",
	[OPEN_BRACE] = "(",
	[CLOSE_BRACE] = ")",
	[REDIRECT_IN] = "<",
	[REDIRECT_OUT] = ">",
	};
	t_lexer_tok			token;
	int					type;

	type = get_operand_token(operand_type, s);
	if (type == -1)
		return (0);
	token.content = NULL;
	token.type = type;
	if (add_vector(lexer, &token, 1) == -1)
		return (-1);
	return (ft_strlen(operand_type[type]));
}

static int	get_operand_token(const char *operand_type[], char *s)
{
	size_t	i;

	i = 0;
	while (i <= REDIRECT_OUT)
	{
		if (ft_strncmp(operand_type[i], s, ft_strlen(operand_type[i])) == 0)
			return (i);
		++i;
	}
	return (-1);
}
