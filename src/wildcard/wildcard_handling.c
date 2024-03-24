/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 06:43:48 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 20:55:09 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "lexer.h"
#include "ft_mem.h"
#include "vector.h"
#include "wildcard.h"
#include <stdio.h>

void	print_pattern(t_wildcard *wildcard)
{
	t_pattern	*pattern;
	int			i;

	i = 0;
	while (i < (int)wildcard->patterns.size)
	{
		pattern = at_vector(&wildcard->patterns, i);
		print_lexer(&pattern->pattern);
		printf("lexer_type = %d", pattern->type);
		++i;
	}
}

void	clear_wildcard(t_wildcard *wildcard)
{
	t_pattern	*pattern;
	size_t		i;

	i = 0;
	while (i < wildcard->patterns.size)
	{
		pattern = at_vector(&wildcard->patterns, i);
		clear_lexer(&pattern->pattern);
		pattern->type = 0;
		++i;
	}
	clear_vector(&wildcard->patterns);
}

int	wildcard_handling(t_env *env, t_lexer *filenames, char *raw_pattern)
{
	t_wildcard	wildcard;

	ft_memset(&wildcard, 0, sizeof(t_wildcard));
	init_vector(&wildcard.patterns, sizeof(t_pattern));
	init_lexer(filenames);
	wildcard.globignore = ms_getenv(env, "GLOBIGNORE");
	if (create_pattern(&wildcard, raw_pattern) == -1)
	{
		clear_wildcard(&wildcard);
		return (-1);
	}
	print_pattern(&wildcard);
	if (compare_pattern(&wildcard, filenames) == -1)
		return (-1);
	sort_filenames(filenames);
	print_lexer(filenames);
	clear_wildcard(&wildcard);
	(void)filenames;
	return (0);
}
