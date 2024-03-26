/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:19:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/26 05:10:42 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include "wildcard.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int get_starting_path(t_wildcard *wildcard);

int	add_custom_path(t_wildcard *wildcard, t_lexer *filenames)
{
	char		*tmp_wd;
	t_lexer_tok	*tok;
	size_t		i;

	tmp_wd = getcwd(NULL, 0);
	if (tmp_wd == NULL)
		return (-1);
	if (ft_strcmp(tmp_wd, wildcard->wd) == 0)
	{
		free(tmp_wd);
		return (0);
	}
	free(tmp_wd);
	i = 0;
	while (i < filenames->size)
	{
		tok = at_vector(filenames, i);
		tok->content = ft_strjoin_fs2(wildcard->wd, tok->content);
		if (tok->content == NULL)
			return (-1);
		++i;
	}
	return (0);
}

int	compare_pattern(t_wildcard *wildcard, t_lexer *filenames)
{
	if (get_starting_path(wildcard) == -1)
		return (-1);
	if (get_matching_dirname(wildcard, filenames, 0) == -1)
		return (-1);
	if (wildcard->nb_dir < (int)wildcard->patterns.size)
	{
		if (get_matching_filenames(wildcard, filenames) == -1)
			return (-1);
	}
	if (add_custom_path(wildcard, filenames) == -1)
		return (-1);
	return (0);
}

static int	get_starting_path(t_wildcard *wildcard)
{
	t_pattern	*pattern;
	t_lexer_tok *tok;

	pattern = at_vector(&wildcard->patterns, 0);
	tok = at_vector(&pattern->pattern, 0);
	if (pattern->type == DIRECTORY && tok->type == WORD)
	{
		wildcard->globignore = NULL;
		wildcard->wd = ft_strdup(tok->content);
		if (wildcard->wd == NULL)
			return (-1);
		clear_lexer(&pattern->pattern);
		remove_vector(&wildcard->patterns, 0);
		--wildcard->nb_dir;
	}
	else 
	{
		wildcard->wd = getcwd(NULL, 0);
		if (wildcard->wd == NULL)
			return (-1);
	}
	if (wildcard->nb_dir > 1)
		wildcard->globignore = NULL;
	wildcard->wd_size = ft_strlen(wildcard->wd);
	printf("wd in init == %s\n", wildcard->wd);
	return (0);
}
