/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:19:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/12 01:06:38 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "vector.h"
#include "wildcard.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static int	get_starting_path(t_wild *wildcard);
static int	add_absolute_path(t_wild *wildcard, t_vector *filenames);
static int	set_absolute_path(t_wild *wildcard, t_pattern *pattern, char *path);
static int	set_relative_path(t_wild *wildcard);

int	compare_pattern(t_wild *wildcard, t_vector *filenames)
{
	if (get_starting_path(wildcard) == -1)
	{
		if (errno == ENOMEM)
			return (-1);
		return (0);
	}
	if (get_matching_dirname(wildcard, filenames, 0) == -1)
		return (-1);
	if (wildcard->nb_dir < wildcard->patterns.size)
	{
		if (get_matching_filenames(wildcard, filenames) == -1)
			return (-1);
	}
	if (wildcard->absolute_path)
	{
		if (add_absolute_path(wildcard, filenames) == -1)
			return (-1);
	}
	return (0);
}

static int	get_starting_path(t_wild *wildcard)
{
	t_pattern	*pattern;
	t_lexer_tok	*tok;

	pattern = at_vector(&wildcard->patterns, 0);
	tok = at_vector(&pattern->pattern, 0);
	if (pattern->type == DIRECTORY && ft_strncmp(tok->content, "/", 1) == 0)
	{
		if (set_absolute_path(wildcard, pattern, tok->content) == -1)
			return (-1);
	}
	else
	{
		if (set_relative_path(wildcard) == -1)
			return (-1);
	}
	if (wildcard->nb_dir > 1)
		wildcard->globignore = NULL;
	wildcard->wd_size = ft_strlen(wildcard->wd);
	return (0);
}

static int	set_absolute_path(t_wild *wildcard, t_pattern *pattern, char *path)
{
	wildcard->globignore = NULL;
	wildcard->wd = ft_strdup(path);
	if (wildcard->wd == NULL)
		return (-1);
	clear_lexer(&pattern->pattern);
	remove_vector(&wildcard->patterns, 0);
	--wildcard->nb_dir;
	wildcard->absolute_path = 1;
	return (0);
}

static int	set_relative_path(t_wild *wildcard)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		return (-1);
	wildcard->wd = ft_strjoin(tmp, "/");
	free(tmp);
	if (wildcard->wd == NULL)
		return (-1);
	return (0);
}

static int	add_absolute_path(t_wild *wildcard, t_vector *filenames)
{
	char		**s;
	size_t		i;
	char		*tmp_wd;

	i = 0;
	while (i < filenames->size)
	{
		s = at_vector(filenames, i);
		tmp_wd = *s;
		*s = ft_strjoin(wildcard->wd, tmp_wd);
		if (*s == NULL)
		{
			free(tmp_wd);
			return (-1);
		}
		++i;
		free(tmp_wd);
	}
	return (0);
}
