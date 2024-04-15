/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 06:43:48 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/15 02:54:33 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include "signals.h"
#include "wildcard.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void	init_wildcard(t_wild *wildcard, t_env *env, t_vector *filenames);
static void	clear_wildcard(t_wild *wildcard);

int	wildcard_handling(t_env *env, t_vector *filenames, char *raw_pattern)
{
	t_wild	wildcard;

	errno = 0;
	init_wildcard(&wildcard, env, filenames);
	if (create_pattern(&wildcard, raw_pattern) == -1)
	{
		clear_wildcard(&wildcard);
		return (-1);
	}
	if (compare_pattern(&wildcard, filenames) == -1)
	{
		clear_wildcard(&wildcard);
		return (-1);
	}
	clear_wildcard(&wildcard);
	if (g_sig == SIGINT)
		return (0);
	sort_filenames(filenames, 0, filenames->size - 1);
	return (add_backslash(filenames));
}

static void	init_wildcard(t_wild *wildcard, t_env *env, t_vector *filenames)
{
	ft_memset(wildcard, 0, sizeof(t_wild));
	init_vector(&wildcard->patterns, sizeof(t_pattern));
	init_vector(&wildcard->glob_patterns, sizeof(t_pattern));
	wildcard->f_lst_ptr = filenames;
	wildcard->wd = NULL;
	wildcard->globignore = ms_getenv(env, "GLOBIGNORE");
}

static void	clear_wildcard(t_wild *wildcard)
{
	t_pattern	*pattern;
	size_t		i;

	free(wildcard->wd);
	i = 0;
	while (i < wildcard->patterns.size)
	{
		pattern = at_vector(&wildcard->patterns, i);
		clear_lexer(&pattern->pattern);
		pattern->type = 0;
		++i;
	}
	i = 0;
	while (i < wildcard->glob_patterns.size)
	{
		pattern = at_vector(&wildcard->glob_patterns, i);
		clear_lexer(&pattern->pattern);
		pattern->type = 0;
		++i;
	}
	clear_vector(&wildcard->glob_patterns);
	clear_vector(&wildcard->patterns);
}
