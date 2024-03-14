/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matching_filenames.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 06:05:17 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/14 10:20:26 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include "wildcard.h"
#include <dirent.h>
#include <stdio.h>

static int	add_match_tok(t_lexer *filenames, char *s);
static int	get_files_ls(t_env *env, t_lexer *matches);
static int	get_match(t_lexer *filenames, t_lexer *pattern, char *r_pattern);
static int	is_wildcard_in_pattern(t_lexer *pattern);

int	get_matching_filenames(t_env *env, t_lexer *filenames, t_lexer_tok *token)
{
	t_lexer	pattern;

	init_lexer(filenames);
	if (get_files_ls(env, filenames) == -1)
	{
		clear_lexer(filenames);
		return (-1);
	}
	if (fill_pattern(&pattern, token->content) == -1)
	{
		clear_lexer(&pattern);
		clear_lexer(filenames);
		return (-1);
	}
	if (get_match(filenames, &pattern, token->content) == -1)
	{
		clear_lexer(filenames);
		return (-1);
	}
	sort_filenames(filenames);
	return (0);
}

static int	get_match(t_lexer *filenames, t_lexer *pattern, char *raw_pattern)
{
	size_t		i;
	t_lexer		matching_filenames;
	t_lexer_tok	*match_tok;

	i = 0;
	init_lexer(&matching_filenames);
	while (i < filenames->size && is_wildcard_in_pattern(pattern))
	{
		match_tok = at_vector(filenames, i);
		if (is_wildcard_match(pattern, raw_pattern, match_tok->content) == 1)
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

static int	get_files_ls(t_env *env, t_lexer *filenames)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*wd;

	wd = ms_getenv(env, "PWD");
	if (wd == NULL)
		return (-1);
	dir = opendir(wd);
	if (dir == NULL)
	{
		perror("opendir");
		return (-1);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (add_match_tok(filenames, entry->d_name) == -1)
		{
			closedir(dir);
			return (-1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

static int	is_wildcard_in_pattern(t_lexer *pattern)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	while (i < pattern->size)
	{
		token = at_vector(pattern, i);
		if (token->type == 0)
			return (1);
		++i;
	}
	return (0);
}

static int	add_match_tok(t_lexer *matches, char *s)
{
	t_lexer_tok	token;

	token.content = ft_strdup(s);
	if (token.content == NULL)
		return (-1);
	token.type = WORD;
	if (add_vector(matches, &token, 1) == -1)
		return (-1);
	return (0);
}
