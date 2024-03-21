/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:57:23 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/21 07:50:56 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include "ft_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int		remove_quotes(t_lexer_tok *token);
static ssize_t	remove_inquote(t_lexer_tok *token, t_vector *new, size_t i);
static ssize_t	remove_dquote(t_lexer_tok *token, t_vector *new, size_t i);

int	quote_removal(t_lexer *lexer)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == WORD)
		{
			if (remove_quotes(token) == -1)
				return (-1);
		}
		++i;
	}
	return (0);
}

static int	remove_quotes(t_lexer_tok *token)
{
	t_vector	new;
	ssize_t		i;

	init_vector(&new, sizeof(char));
	i = 0;
	while (token->content[i])
	{
		if (token->content[i] == '\\')
		{
			++i;
			if (add_vector(&new, token->content + i, 1) == -1)
				return (-1);
		}
		else if (is_quote(token->content[i]))
			i = remove_inquote(token, &new, i);
		else if (add_vector(&new, token->content + i, 1) == -1)
			return (-1);
		if (i == -1)
			return (-1);
		++i;
	}
	free(token->content);
	token->content = new.array;
	return (0);
}

static ssize_t	remove_inquote(t_lexer_tok *token, t_vector *new, size_t i)
{
	const char	quote = token->content[i];
	size_t		j;

	if (quote == '\'')
	{
		++i;
		j = i;
		while (token->content[i] != '\'')
			++i;
		if (add_vector(new, token->content + j, j - i) == -1)
			return (-1);
		return (i);
	}
	return (remove_dquote(token, new, i + 1));
}

// this is a terrible way to fix this, TODO: remove
static ssize_t	remove_dquote(t_lexer_tok *token, t_vector *new, size_t i)
{
	int	err;

	if (add_vector(new, "", 0) == -1)
		return (-1);
	while (token->content[i] != '"')
	{
		if (token->content[i] == '\\')
		{
			if (ft_strchr("$\\\"", token->content[i + 1]) == NULL)
				err = add_vector(new, token->content + i, 2);
			else
				err = add_vector(new, token->content + i + 1, 1);
			++i;
		}
		else
			err = add_vector(new, token->content + i, 1);
		if (err == -1)
			return (-1);
		++i;
	}
	return (i);
}
