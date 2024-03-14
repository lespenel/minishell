#include "lexer.h"
#include "vector.h"
#include <stdio.h>

static int	syntax_checker(t_lexer *lexer, int index, int brace);
static int	is_problem(t_lexer_tok *tok1, t_lexer_tok *tok2);
static int	is_redirect_problem(t_lexer_tok *tok1, t_lexer_tok *tok2);
static int	is_logical(t_lexer_tok *tok1);

int	validate_input(t_lexer *lexer)
{
	if (lexer->size == 0)
		return (0);
	if (syntax_checker(lexer, 0, 0) == -1)
		return (-1);
	return (0);
}

static int	syntax_checker(t_lexer *lexer, int index, int brace)
{
	t_lexer_tok	*token;

	token = at_vector(lexer, index);
	if (token->type == OPEN_BRACE)
		brace++;
	else if (token->type == CLOSE_BRACE)
	{
		if (brace <= 0)
			return (dprintf(2, SYNTAX_ERR, ")"), -1);
		brace++;
	}
	else if (token->type == NEWLINE)
	{
		if (brace == 0)
			return (0);
		return (dprintf(2, SYNTAX_ERR, "("), -1);
	}
	else if (is_problem(token, at_vector(lexer, index + 1)))
		return (-1);
	return (syntax_checker(lexer, index + 1, brace));
}

static int	is_problem(t_lexer_tok *tok1, t_lexer_tok *tok2)
{
	if (is_redirect_problem(tok1, tok2))
	{
		return (dprintf(2, SYNTAX_ERR, tok2->content));
	}
	if (is_logical(tok1) && (is_logical(tok2) || tok2->type == NEWLINE))
		return (dprintf(2, SYNTAX_ERR, tok1->content));
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
