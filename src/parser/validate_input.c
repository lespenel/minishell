/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 02:12:59 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/03 03:17:09 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "vector.h"
#include "ft_io.h"

static int	syntax_checker(t_lexer *lexer, int index, int brace);
static int	is_problem(t_lexer_tok *tok1, t_lexer_tok *tok2);
static int	is_redirect_problem(t_lexer_tok *tok1, t_lexer_tok *tok2);
static int	is_logical(t_lexer_tok *tok1);

int	validate_input(t_lexer *lexer)
{
	t_lexer_tok	*token;
	int			ret;

	if (lexer->size == 0)
		return (0);
	token = at_vector(lexer, 0);
	if (is_logical(token))
		return (syntax_error(token->type));
	ret = syntax_checker(lexer, 0, 0);
	if (ret == -1)
		return (-1);
	if (ret == 0 && get_here_doc(lexer) == -1)
		return (-1);
	return (ret);
}

static int	syntax_checker(t_lexer *lexer, int index, int brace)
{
	t_lexer_tok	*token;

	token = at_vector(lexer, index);
	if (token->type == OPEN_BRACE)
		++brace;
	else if (token->type == CLOSE_BRACE)
	{
		if (brace <= 0)
			return (syntax_error(CLOSE_BRACE));
		--brace;
	}
	else if (token->type == NEWLINE)
	{
		if (brace == 0)
			return (0);
		return (syntax_error(OPEN_BRACE));
	}
	if (is_problem(token, at_vector(lexer, index + 1)))
		return (1);
	return (syntax_checker(lexer, index + 1, brace));
}

static int	is_problem(t_lexer_tok *tok1, t_lexer_tok *tok2)
{
	if (tok1->type == OPEN_BRACE && is_logical(tok2))
		return (syntax_error(tok2->type));
	if (tok1->type == CLOSE_BRACE && tok2->type == WORD)
		return (syntax_error(tok2->type));
	if (tok2->type == OPEN_BRACE && tok1->type == WORD)
		return (syntax_error(tok2->type));
	if (tok2->type == CLOSE_BRACE && tok1->type != WORD
		&& tok1->type != CLOSE_BRACE)
		return (syntax_error(tok2->type));
	if (is_redirect_problem(tok1, tok2))
		return (syntax_error(tok2->type));
	if (is_logical(tok1) && (is_logical(tok2) || tok2->type == NEWLINE))
		return (syntax_error(tok1->type));
	return (0);
}

static int	is_redirect_problem(t_lexer_tok *tok1, t_lexer_tok *tok2)
{
	if (tok1->type == HERE_DOC && tok2->type != WORD)
		return (1);
	if (tok1->type == APPEND && tok2->type != WORD)
		return (1);
	if (tok1->type == REDIRECT_IN && tok2->type != WORD)
		return (1);
	if (tok1->type == REDIRECT_OUT && tok2->type != WORD)
		return (1);
	return (0);
}

static int	is_logical(t_lexer_tok *tok)
{
	if (tok->type == PIPE || tok->type == LOGICAL_OR
		|| tok->type == LOGICAL_AND)
		return (1);
	return (0);
}
