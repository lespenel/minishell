/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_glob_pattern.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 02:45:28 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/05 03:50:47 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "util.h"
#include "wildcard.h"
#include <stdlib.h>

static	int	fill_glob_pattern(t_wild *wild, char *entry, t_pattern *pattern);

int	create_glob_pattern(t_wild *wild)
{
	char		*entry;
	t_pattern	pattern;

	if (wild->globignore == NULL)
		return (0);
	entry = ft_strdup(wild->globignore);
	if (entry == NULL)
		return (-1);
	if (fill_glob_pattern(wild, entry, &pattern) == -1)
	{
		clear_lexer(&pattern.pattern);
		free(entry);
		return (-1);
	}
	free(entry);
	return (0);
}

static	int	fill_glob_pattern(t_wild *wild, char *entry, t_pattern *pattern)
{
	char	*tok;

	tok = ft_strtok(entry, ":");
	while (tok)
	{
		if (ms_strchr(tok, '/'))
			pattern->type = FILENAME;
		else
			pattern->type = NO_STAR;
		if (fill_pattern(&pattern->pattern, tok) == -1
			|| add_vector(&wild->glob_patterns, pattern, 1) == -1)
			return (-1);
		tok = ft_strtok(NULL, ":");
	}
	return (0);
}
