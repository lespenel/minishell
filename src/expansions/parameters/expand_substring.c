/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_substring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:50:12 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/28 04:26:18 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minishell.h"
#include "ft_string.h"
#include "expander.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

static ssize_t	dq_variable(t_ms *ms, t_vector *new, char *s, size_t i);
static ssize_t	treat_dquote(t_ms *ms, t_vector *new, char *s);
static int		add_escaping_dq(t_vector *vector, char *s);

ssize_t	expand_substr(t_ms *ms, t_vector *new, char *s)
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
	return (treat_noquote(ms, new, s));
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
	value = ms_getnenv(&ms->env, s + j, i - j);
	if (value != NULL)
	{
		if (add_escaping_dq(new, value) == -1)
			return (-1);
	}
	return (i);
}

static int	add_escaping_dq(t_vector *vector, char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr("\\$\"", s[i]))
		{
			if (add_vector(vector, "\\", 1) == -1)
				return (-1);
		}
		if (add_vector(vector, s + i, 1) == -1)
			return (-1);
		++i;
	}
	return (0);
}
