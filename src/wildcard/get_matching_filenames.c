/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matching_filenames.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 06:05:17 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/13 06:23:23 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "ft_string.h"
#include "stdio.h"
#include <dirent.h>

static int	get_files_ls(t_env *env, t_lexer *matches);
static int	get_match_from_filenames(t_lexer *match, char *s);
static int	add_match_tok(t_lexer *matches, char *s);

int	get_matching_filenames(t_env *env, t_lexer *filenames, t_lexer_tok *token)
{
	init_lexer(filenames);
	if (get_files_ls(env, filenames) == -1)
	{
		clear_lexer(filenames);
		return (-1);
	}
	if (get_match_from_filenames(filenames, token->content) == -1)
	{
		clear_lexer(filenames);
		return (-1);
	}
	return (0);
}

static int	get_match_from_filenames(t_lexer *match, char *s)
{
	size_t		i;
	t_lexer		new_match;
	t_lexer_tok	*match_tok;

	i = 0;
	init_lexer(&new_match);
	while (i < match->size)
	{
		match_tok = at_vector(match, i);
		if (is_wildcard_match(s, match_tok->content))
		{
			if (add_match_tok(&new_match, match_tok->content) == -1)
				return (-1);
		}
		i++;
	}
	clear_lexer(match);
	*match = new_match;
	return (0);
}

static int	get_files_ls(t_env *env, t_lexer *matches)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*wd;

	wd = ms_getenv(env, "PWD");
	if (wd == NULL)
		return (dprintf(2, "minishell: ms_get_env error\n"), -1);
	dir = opendir(wd);
	if (dir == NULL)
		return (perror("opendir"), -1);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (add_match_tok(matches, entry->d_name) == -1)
		{
			closedir(dir);
			return (-1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
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
