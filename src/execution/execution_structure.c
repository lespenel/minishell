/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 01:41:37 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/22 03:02:11 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include <stdio.h>

static int	create_subshell(t_lexer *lexer, t_lexer_tok *shtoken, size_t i);

int	execution_structure(t_lexer *lexer)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == OPEN_BRACE)
		{
			token->type = SUBSHELL;
			if (create_subshell(lexer, token, i) == -1)
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

	dprintf(2, "emter subshell crea\n");
	++i;
	init_lexer(&subshell);
	token = at_vector(lexer, i);
	while (token->type != CLOSE_BRACE)
	{
		dprintf(2, "creating subshell tok=%d content=%s\n", token->type, token->content);
		if (token->type == OPEN_BRACE)
		{
			newtoken.type = SUBSHELL;
			if (create_subshell(lexer, &newtoken, i) == -1)
				return (-1);
			remove_vector(lexer, i);
			if (add_vector(&subshell, &newtoken, 1) == -1)
				return (-1);
		}
		else
		{
			if (add_vector(&subshell, at_vector(lexer, i), 1) == -1)
				return (-1);
			remove_vector(lexer, i);
		}
		token = at_vector(lexer, i);
	}
	remove_vector(lexer, i);
	shtoken->subshell = subshell;
	dprintf(2, "exit subshell crea\n");
	return (0);
}
