/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matching_filenames.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 06:05:17 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 13:58:22 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include "wildcard.h"
#include <dirent.h>

static int	get_match(t_lexer *filenames, t_lexer *pattern);

int	get_match_filenames(t_env *env, t_lexer *filenames, t_lexer_tok *token)
{
	t_lexer	pattern;

	init_lexer(filenames);
	if (get_files_ls(env, filenames) == -1)
	{
		clear_lexer(filenames);
		return (-1);
	}
	if (fill_pattern(&pattern, token->content) == -1
		|| remove_backslash(&pattern) == -1)
	{
		clear_lexer(&pattern);
		clear_lexer(filenames);
		return (-1);
	}
	if (get_match(filenames, &pattern) == -1)
	{
		clear_lexer(filenames);
		return (-1);
	}
	sort_filenames(filenames);
	return (0);
}

static int	get_match(t_lexer *filenames, t_lexer *pattern)
{
	size_t		i;
	t_lexer		matching_filenames;
	t_lexer_tok	*match_tok;

	i = 0;
	init_lexer(&matching_filenames);
	while (i < filenames->size)
	{
		match_tok = at_vector(filenames, i);
		if (is_wildcard_match(pattern, match_tok->content) == 1)
		{
			if (add_match_tok(&matching_filenames, match_tok->content) == -1)
			{
				clear_lexer(pattern);
				clear_lexer(&matching_filenames);
				return (-1);
			}
		}
		++i;
	}
	clear_lexer(pattern);
	clear_lexer(filenames);
	*filenames = matching_filenames;
	return (0);
}
