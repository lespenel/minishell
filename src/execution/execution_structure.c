/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 01:41:37 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/22 05:37:48 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include "ft_mem.h"
#include <stdio.h>

static int	create_subshells(t_lexer *lexer);
static int	fill_newtoken(t_lexer *lexer, size_t i, t_lexer_tok *newtoken);
static int	create_subshell(t_lexer *lexer, t_lexer_tok *shtoken, size_t i);
static int	simplify_tokens(t_lexer *lexer);

int	execution_structure(t_lexer *lexer)
{
	if (create_subshells(lexer) == -1)
		return (-1);
	if (simplify_tokens(lexer) == -1)
		return (-1);
	return (0);
}

static int	create_subshells(t_lexer *lexer)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == OPEN_BRACE)
		{
			if (create_subshell(lexer, token, i + 1) == -1)
				return (-1);
		}
		++i;
	}
	return (0);
}

static int	create_subshell(t_lexer *lexer, t_lexer_tok *shtoken, size_t i)
{
	t_lexer_tok	*token;
	t_lexer_tok	newtoken;
	t_lexer		subshell;

	init_lexer(&subshell);
	token = at_vector(lexer, i);
	shtoken->type = SUBSHELL;
	while (token->type != CLOSE_BRACE)
	{
		if (fill_newtoken(lexer, i, &newtoken) == -1)
		{
			clear_lexer(&subshell);
			return (-1);
		}
		if (add_vector(&subshell, &newtoken, 1) == -1)
			return (-1);
		remove_vector(lexer, i);
		token = at_vector(lexer, i);
	}
	remove_vector(lexer, i);
	shtoken->subshell = subshell;
	return (0);
}

static int	fill_newtoken(t_lexer *lexer, size_t i, t_lexer_tok *newtoken)
{
	const t_lexer_tok	*token = at_vector(lexer, i);

	if (token->type == OPEN_BRACE)
	{
		if (create_subshell(lexer, newtoken, i + 1) == -1)
		{
			clear_lexer(lexer);
			return (-1);
		}
	}
	else
		*newtoken = *((t_lexer_tok *)at_vector(lexer, i));
	return (0);
}

static int	simplify_tokens(t_lexer *lexer)
{
	size_t		i;
	t_lexer_tok	cmd;

	ft_memset(&cmd, 0, sizeof(t_lexer_tok));
	cmd.type = COMMAND;
	i = 0;
	while (i < lexer->size)
	{
		++i;
	}
	return (0);
}
