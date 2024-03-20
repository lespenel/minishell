/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_noquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:49:48 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/20 00:52:25 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minishell.h"
#include "lexer.h"
#include "expander.h"
#include "ft_string.h"
#include <stdlib.h>

static ssize_t	nq_variable(t_ms *ms, t_lexer *lex, t_vector *new, char *s);
static ssize_t	expand_nq_variable(t_lexer *lex, t_vector *new, char *value);
static int		add_word_lex(t_lexer *lex, t_vector *word);

ssize_t	treat_noquote(t_ms *ms, t_lexer *lex, t_vector *new, char *s)
{
	size_t	i;
	ssize_t	j;

	i = next_char(s, -1);
	j = 0;
	while (s[i] && s[i] != '"' && s[i] != '\'')
	{
		if (s[i] == '$')
		{
			if (i - j > 0 && add_vector(new, s + j, i - j) == -1)
				return (-1);
			++i;
			j = nq_variable(ms, lex, new, s + i);
			if (j == -1)
				return (-1);
			i += j;
			j = i;
		}
		else
			i = next_char(s, i);
	}
	if (i - j > 0 && add_vector(new, s + j, i - j) == -1)
		return (-1);
	return (i);
}

static ssize_t	nq_variable(t_ms *ms, t_lexer *lex, t_vector *new, char *s)
{
	size_t	i;
	char	*value;

	i = 0;
	while (ft_strchr("\"'\\$\0", s[i]) == NULL)
		++i;
	value = ms_getenv(&ms->env, s, i);
	if (value != NULL)
	{
		if (expand_nq_variable(lex, new, value) == -1)
			return (-1);
	}
	return (i);
}

static ssize_t	expand_nq_variable(t_lexer *lexer, t_vector *new, char *value)
{
	char		*var;
	char		*tok;

	var = ft_strdup(value);
	if (var == NULL)
		return (-1);
	tok = ft_strtok(var, " ");
	while (tok)
	{
		if (add_escaping(new, tok) == -1)
		{
			free(var);
			return (-1);
		}
		tok = ft_strtok(NULL, " ");
		if (tok && add_word_lex(lexer, new) == -1)
		{
			free(var);
			return (-1);
		}
	}
	free(var);
	return (0);
}

static int	add_word_lex(t_lexer *lexer, t_vector *word)
{
	t_lexer_tok	token;

	token.type = WORD;
	token.content = word->array;
	if (add_vector(lexer, &token, 1) == -1)
		return (-1);
	init_vector(word, sizeof(char));
	return (0);
}
