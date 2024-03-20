/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_substring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:50:12 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/20 00:52:13 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include "ft_string.h"
#include "expander.h"

static ssize_t	dq_variable(t_ms *ms, t_vector *new, char *s, size_t i);
static ssize_t	treat_dquote(t_ms *ms, t_vector *new, char *s);

ssize_t	expand_substr(t_ms *ms, t_lexer *lexer, t_vector *new, char *s)
{
	size_t	i;

	if (*s == '\'')
	{
		i = next_char(s, 0);
		while (s[i] != '\'')
			i = next_char(s, i);
		++i;
		if (add_vector(new, s, i) == -1)
			return (-1);
		return (i);
	}
	if (*s == '"')
		return (treat_dquote(ms, new, s));
	return (treat_noquote(ms, lexer, new, s));
}

static ssize_t	treat_dquote(t_ms *ms, t_vector *new, char *s)
{
	ssize_t	i;
	size_t	j;

	i = next_char(s, 0);
	j = 0;
	while (s[i] != '"')
	{
		if (s[i] == '$')
		{
			if (add_vector(new, s + j, i - j) == -1)
				return (-1);
			i = dq_variable(ms, new, s, i + 1);
			if (i == -1)
				return (-1);
			j = i;
		}
		else
			i = next_char(s, i);
	}
	++i;
	if (add_vector(new, s + j, i - j) == -1)
		return (-1);
	return (i);
}

static ssize_t	dq_variable(t_ms *ms, t_vector *new, char *s, size_t i)
{
	size_t	j;
	char	*value;

	j = i;
	while (ft_strchr("\"'\\$", s[i]) == NULL)
		++i;
	value = ms_getenv(&ms->env, s + j, i - j);
	if (value != NULL)
	{
		if (add_escaping(new, value) == -1)
			return (-1);
	}
	return (i);
}
