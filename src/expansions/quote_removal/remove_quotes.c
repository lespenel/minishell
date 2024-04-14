/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 06:15:45 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/12 06:16:15 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include "ft_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int		fill_vector_without_quote(t_vector *new, char *s);
static ssize_t	remove_inquote(char *s, t_vector *new, size_t i);
static ssize_t	remove_dquote(char *s, t_vector *new, size_t i);

int	remove_quotes(char **s)
{
	t_vector	new;

	init_vector(&new, sizeof(char));
	if (add_vector(&new, "", 0) == -1)
	{
		clear_vector(&new);
		return (-1);
	}
	if (fill_vector_without_quote(&new, *s) == -1)
	{
		clear_vector(&new);
		return (-1);
	}
	free(*s);
	*s = new.array;
	return (0);
}

static int	fill_vector_without_quote(t_vector *new, char *s)
{
	ssize_t		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\\')
		{
			++i;
			if (add_vector(new, s + i, 1) == -1)
				return (-1);
		}
		else if (is_quote(s[i]))
			i = remove_inquote(s, new, i);
		else if (add_vector(new, s + i, 1) == -1)
			return (-1);
		if (i == -1)
			return (-1);
		++i;
	}
	return (0);
}

static ssize_t	remove_inquote(char *s, t_vector *new, size_t i)
{
	const char	quote = s[i];
	size_t		j;

	if (quote == '\'')
	{
		++i;
		j = i;
		while (s[i] != '\'')
			++i;
		if (add_vector(new, s + j, i - j) == -1)
			return (-1);
		return (i);
	}
	return (remove_dquote(s, new, i + 1));
}

static ssize_t	remove_dquote(char *s, t_vector *new, size_t i)
{
	int	err;

	while (s[i] != '"')
	{
		if (s[i] == '\\')
		{
			if (ft_strchr("$\\\"", s[i + 1]) == NULL)
				err = add_vector(new, s + i, 2);
			else
				err = add_vector(new, s + i + 1, 1);
			++i;
		}
		else
			err = add_vector(new, s + i, 1);
		if (err == -1)
			return (-1);
		++i;
	}
	return (i);
}
