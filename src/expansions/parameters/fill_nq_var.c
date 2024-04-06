/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nq_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 06:42:35 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/06 06:43:56 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "vector.h"
#include "expander.h"
#include <stdlib.h>

static char	*remove_whitespaces(char *s, const char *ifs);
static int	add_escaping_nq(t_vector *vector, char *s);

int	fill_nq_var(t_vector *tab, t_vector *new, char *value, const char *ifs)
{
	char		*var;
	char		*tok;

	var = ft_strdup(value);
	if (var == NULL)
		return (-1);
	tok = remove_whitespaces(var, ifs);
	tok = ft_strtok_ifs(tok, ifs);
	while (tok)
	{
		if (add_escaping_nq(new, tok) == -1)
		{
			free(var);
			return (-1);
		}
		tok = ft_strtok_ifs(NULL, ifs);
		if (tok && add_word_tab(tab, new) == -1)
		{
			free(var);
			return (-1);
		}
	}
	free(var);
	return (0);
}

static char	*remove_whitespaces(char *s, const char *ifs)
{
	size_t	i;

	while (ft_strchr(" \t\n", *s) != NULL && ft_strchr(ifs, *s) != NULL)
		++s;
	if (*s == '\0')
		return (s);
	i = ft_strlen(s);
	--i;
	while (ft_strchr(" \t\n", *s) != NULL && ft_strchr(ifs, *s) != NULL)
	{
		s[i] = '\0';
		--i;
	}
	return (s);
}

static int	add_escaping_nq(t_vector *vector, char *s)
{
	size_t	i;

	if (add_vector(vector, "", 0) == -1)
		return (-1);
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
