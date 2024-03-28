/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_noquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:49:48 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/28 02:58:01 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minishell.h"
#include "expander.h"
#include "ft_string.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

static ssize_t	nq_variable(t_ms *ms, t_vector *new, char *s);
static int		add_escaping_nq(t_vector *vector, char *s);

ssize_t	treat_noquote(t_ms *ms, t_vector *new, char *s)
{
	size_t	i;
	ssize_t	j;

	i = next_char(s, -1);
	j = 0;
	while (s[i] && s[i] != '"' && s[i] != '\'')
	{
		if (s[i] == '$')
		{
			if (add_vector(new, s + j, i - j) == -1)
				return (-1);
			++i;
			j = nq_variable(ms, new, s + i);
			if (j == -1)
				return (-1);
			i += j;
			j = i;
		}
		else
			i = next_char(s, i);
	}
	if (add_vector(new, s + j, i - j) == -1)
		return (-1);
	return (i);
}

static ssize_t	nq_variable(t_ms *ms, t_vector *new, char *s)
{
	size_t	i;
	char	*value;

	i = 0;
	while (ft_strchr("\"'\\$\0", s[i]) == NULL)
		++i;
	value = ms_getnenv(&ms->env, s, i);
	if (value != NULL)
	{
		if (add_escaping_nq(new, value) == -1)
			return (-1);
	}
	return (i);
}

static int	add_escaping_nq(t_vector *vector, char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr("\\'\"", s[i]))
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
