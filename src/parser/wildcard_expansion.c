/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/11 08:27:02 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include "wildcard.h"

int	iterate_to_filenames(t_wildcard *match, char *s);
int	add_match_tok(t_wildcard *matches, char *s);

int	expand_wildcard(t_env *env, t_lexer *lexer)
{
	size_t		i;
	t_wildcard	match;
	t_lexer_tok	*token;

	init_lexer(&match);
	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == WORD && ft_strchr(token->content, '*'))
		{
			get_files_ls(env, &match);
			iterate_to_filenames(&match, token->content);
		}
		++i;
	}
	print_lexer(&match);
	return (0);
}

int	iterate_to_filenames(t_wildcard *match, char *s)
{
	size_t		i;
	t_wildcard	new_match;
	t_lexer_tok	*match_tok;

	init_lexer(&new_match);
	i = 0;
	while (i < match->size)
	{
		match_tok = at_vector(match, i);
		if (is_wildcard_match(s, match_tok->content))
		{
			add_match_tok(&new_match, match_tok->content);
			printf("match = %s\n", match_tok->content);
		}
		i++;
	}
	clear_lexer(match);
	*match = new_match;
	return (0);
}

int	add_match_tok(t_wildcard *matches, char *s)
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

int	get_files_ls(t_env *env, t_wildcard *matches)
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
			return (-1);
		entry = readdir(dir);
	}
	print_lexer(matches);
	closedir(dir);
	return (0);
}
