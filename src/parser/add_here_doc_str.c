/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_here_doc_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 02:33:31 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/14 18:37:53 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expander.h"
#include "ft_string.h"
#include "vector.h"
#include <stdio.h>

static int		here_doc_expansion(t_ms *ms, t_vector *new, char *s);
static ssize_t	add_env_variable(t_ms *ms, t_vector *new, char *s, size_t i);

int	add_here_doc_str(t_ms *ms, t_vector *vect, char *s)
{
	size_t		i;
	t_vector	tmp;

	if (s == NULL)
		return (0);
	i = 0;
	init_vector(&tmp, sizeof(char));
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1] == '\n')
			++i;
		else if (add_vector(&tmp, s + i, 1) == -1)
		{
			clear_vector(&tmp);
			return (-1);
		}
		++i;
	}
	if (here_doc_expansion(ms, vect, tmp.array) == -1)
	{
		clear_vector(&tmp);
		return (-1);
	}
	clear_vector(&tmp);
	return (0);
}

static int	here_doc_expansion(t_ms *ms, t_vector *new, char *s)
{
	ssize_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i = add_env_variable(ms, new, s, i + 1);
			if (i == -1)
				return (-1);
		}
		else
		{
			if (s[i] == '\\' && ft_strchr("\\$", s[i + 1]))
				++i;
			if (add_vector(new, s + i, 1) == -1)
				return (-1);
			++i;
		}
	}
	return (0);
}

static ssize_t	add_env_variable(t_ms *ms, t_vector *new, char *s, size_t i)
{
	size_t	j;
	char	*value;

	j = i;
	while (ft_strchr("\"'\\ \t\n$/", s[i]) == NULL)
		++i;
	value = get_parameter_str(ms, s + j, i - j);
	if (value != NULL)
	{
		if (add_vector(new, value, ft_strlen(value)) == -1)
			return (-1);
	}
	return (i);
}
