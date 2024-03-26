/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_globignore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 03:15:59 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/26 07:19:31 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "wildcard.h"

static int	compare_no_star(t_pattern *pattern, char *f_name);

int	compare_globignore(t_wild *wild, char *f_name)
{
	size_t		i;
	t_pattern	*pattern;

	i = 0;
	if (wild->globignore == NULL)
		return (1);
	while (i < wild->glob_patterns.size)
	{
		pattern = at_vector(&wild->glob_patterns, i);
		if (pattern->type == NO_STAR)
		{
			if (compare_no_star(pattern, f_name) == 0)
				return (0);
		}
		if (is_wildcard_match(wild, &pattern->pattern, f_name) == 1)
			return (0);
		++i;
	}
	return (1);
}

static int	compare_no_star(t_pattern *pattern, char *f_name)
{
	t_lexer_tok	*tok;

	if (pattern->type == NO_STAR)
	{
		tok = at_vector(&pattern->pattern, 0);
		if (ft_strcmp(tok->content, f_name) == 0)
			return (0);
	}
	return (1);
}
