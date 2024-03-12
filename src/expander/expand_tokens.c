/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:01:01 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/12 22:01:48 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_string.h"
#include "minishell.h"
#include "vector.h"

static int	expand_word(t_minishell *minishell, t_lexer *lexer, size_t i);
static ssize_t	treat_substring(t_minishell *minishell, t_lexer *lexer, t_vector *new, char *s);
static ssize_t	treat_noquote(t_minishell *minishell, t_lexer *lexer, t_vector *new, char *s);
static ssize_t	kaboul(t_lexer *lexer, t_vector *new, char *value);
static ssize_t	treat_dquote(t_minishell *minishell, t_lexer *lexer, t_vector *new, char *s);
static ssize_t	treat_squote(t_minishell *minishell, t_lexer *lexer, t_vector *new, char *s);

int	expand_tokens(t_minishell *minishell, t_lexer *lexer)
{
	size_t		i;
	ssize_t		res;
	t_lexer_tok	*token;

	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == WORD)
		{
			res = expand_word(minishell, lexer, i);
			if (res == -1)
				return (-1);
			i += res;
		}
		else
			++i;
	}
	return (0);
}
//TODO : handle only one variable expanding into nothing
static int	expand_word(t_minishell *minishell, t_lexer *lexer, size_t i)
{
	char	*word;
	ssize_t	wlen;
	size_t	j;
	t_lexer	newlexer;
	t_vector	newstring;

	init_lexer(&newlexer);
	word = ((t_lexer_tok *)at_vector(lexer, i))->content;
	remove_vector(lexer, i);
	init_vector(&newstring, sizeof(char));
	j = 0;
	while (word[j])
	{
		wlen = treat_substring(minishell, &newlexer, &newstring, word + j);
		if (wlen == -1)
			return (-1);
		j += wlen;
	}
	t_lexer_tok token;
	token.type = WORD;
	token.content = newstring.array;
	add_vector(&newlexer, &token, 1);
	merge_vector(lexer, &newlexer, i);
	ssize_t res = newlexer.size;
	clear_vector(&newlexer);
	return (res);
}

static ssize_t	treat_substring(t_minishell *minishell, t_lexer *lexer, t_vector *new, char *s)
{
	ssize_t	(*f)(t_minishell *, t_lexer *, t_vector *, char *);

	if (*s == '\'')
		f = treat_squote;
	else if (*s == '"')
		f = treat_dquote;
	else
		f = treat_noquote;
	return (f(minishell, lexer, new, s));
}

static ssize_t	treat_noquote(t_minishell *minishell, t_lexer *lexer, t_vector *new, char *s)
{
	size_t	i;
	size_t	j;
	char	*value;

	(void)lexer;
	i = 0;
	j = 0;
	while (s[i] && s[i] != '"' && s[i] != '\'')
	{
		if (s[i] == '$')
		{
			add_vector(new, s + j, i - j);
			++i;
			j = i;
			while (s[i] && s[i] != '"' && s[i] != '\'' && s[i] != '$')
				++i;
			value = ms_getenv(&minishell->env, s + j, i - j);
			if (value != NULL)
				kaboul(lexer, new, value);
			j = i;
		}
		else
			++i;
	}
	add_vector(new, s + j, i - j);
	return (i);
}

static ssize_t	kaboul(t_lexer *lexer, t_vector *new, char *value)
{
	t_lexer_tok	token;
	char		*var;
	char		*tok;

	var = ft_strdup(value);
	tok = ft_strtok(var, " ");
	while (tok)
	{
		add_vector(new, tok, ft_strlen(tok));
		tok = ft_strtok(NULL, " ");
		if (tok)
		{
			token.type = WORD;
			token.content = new->array;
			add_vector(lexer, &token, 1);
			init_vector(new, sizeof(char));
		}
	}
	free(var);
	return (0);
}

static ssize_t	treat_dquote(t_minishell *minishell, t_lexer *lexer, t_vector *new, char *s)
{
	size_t	i;
	size_t	j;
	char	*value;

	(void)lexer;
	i = 1;
	j = 0;
	while (s[i] != '"')
	{
		if (s[i] == '$')
		{
			add_vector(new, s + j, i - j);
			++i;
			j = i;
			while (s[i] != '"' && s[i] != ' ' && s[i] != '$')
				++i;
			value = ms_getenv(&minishell->env, s + j, i - j);
			if (value != NULL)
				add_vector(new, value, ft_strlen(value));
			j = i;
		}
		else
			++i;
	}
	++i;
	add_vector(new, s + j, i - j);
	return (i);
}

static ssize_t	treat_squote(t_minishell *minishell, t_lexer *lexer, t_vector *new, char *s)
{
	size_t	i;

	(void)lexer;
	(void)minishell;
	i = 1;
	while (s[i] != '\'')
		++i;
	++i;
	if (add_vector(new, s, i) == -1)
		return (-1);
	return (i);
}
