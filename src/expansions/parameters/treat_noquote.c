/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_noquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 00:49:48 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/10 03:54:59 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minishell.h"
#include "expander.h"
#include "ft_string.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

static ssize_t	nq_variable(t_ms *ms, t_vector *tab, t_vector *new, char *s);

ssize_t	treat_noquote(t_ms *ms, t_vector *new, char *s, t_vector *tab)
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
			j = nq_variable(ms, tab, new, s + i);
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

static ssize_t	nq_variable(t_ms *ms, t_vector *tab, t_vector *new, char *s)
{
	size_t	i;
	char	*value;

	i = 0;
	while (ft_strchr("\"'\\$/", s[i]) == NULL)
		++i;
	value = get_parameter_str(ms, s, i);
	if (value != NULL)
	{
		if (expand_nq(ms, tab, new, value) == -1)
			return (-1);
	}
	return (i);
}
