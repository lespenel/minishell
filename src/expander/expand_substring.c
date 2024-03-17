/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_substring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:50:12 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/17 21:10:21 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include "ft_string.h"

static ssize_t	treat_noquote(t_minishell *minishell, t_lexer *lexer, t_vector *new, char *s);
static ssize_t	expand_nq_variable(t_lexer *lexer, t_vector *new, char *value);
static int		add_word_lex(t_lexer *lexer, t_vector *word);
static ssize_t	treat_dquote(t_minishell *minishell, t_vector *new, char *s);

ssize_t	expand_substring(t_minishell *minishell, t_lexer *lexer, t_vector *new, char *s)
{
	size_t	i;

	if (*s == '\'')
	{
		i = 1;
		while (s[i] != '\'')
			++i;
		++i;
		if (add_vector(new, s, i) == -1)
			return (-1);
		return (i);
	}
	if (*s == '"')
		return (treat_dquote(minishell, new, s));
	return (treat_noquote(minishell, lexer, new, s));
}

static ssize_t	treat_noquote(t_minishell *minishell, t_lexer *lexer, t_vector *new, char *s)
{
	size_t	i;
	size_t	j;
	char	*value;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '"' && s[i] != '\'')
	{
		if (s[i] == '$')
		{
			if (add_vector(new, s + j, i - j) == -1)
				return (-1);
			++i;
			j = i;
			while (s[i] && s[i] != '"' && s[i] != '\'' && s[i] != '$')
				++i;
			value = ms_getenv(&minishell->env, s + j, i - j);
			if (value != NULL)
			{
				if (expand_nq_variable(lexer, new, value) == -1)
					return (-1);
			}
			j = i;
		}
		else
			++i;
	}
	if (add_vector(new, s + j, i - j) == -1)
		return (-1);
	return (i);
}

static ssize_t	treat_dquote(t_minishell *minishell, t_vector *new, char *s)
{
	size_t	i;
	size_t	j;
	char	*value;

	i = 1;
	j = 0;
	while (s[i] != '"')
	{
		if (s[i] == '$')
		{
			if (add_vector(new, s + j, i - j) == -1)
				return (-1);
			++i;
			j = i;
			while (s[i] != '"' && s[i] != ' ' && s[i] != '$')
				++i;
			value = ms_getenv(&minishell->env, s + j, i - j);
			if (value != NULL)
			{
				if (add_vector(new, value, ft_strlen(value)) == -1)
					return (-1);
			}
			j = i;
		}
		else
			++i;
	}
	++i;
	if (add_vector(new, s + j, i - j) == -1)
		return (-1);
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
		if (add_vector(new, tok, ft_strlen(tok)) == -1)
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
