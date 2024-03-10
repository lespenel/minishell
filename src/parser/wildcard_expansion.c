/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/10 07:09:34 by lespenel         ###   ########.fr       */
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
#include "parser.h"

int	expand_wildcard(t_env *env, t_lexer *lexer)
{
	size_t		i;
	t_wildcard	maches;
	t_lexer_tok	*token;

	init_lexer(&maches);
	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == WORD && ft_strchr(token->content, '*'))
		{
			get_ls_vector(env, &maches);
		}
		++i;
	}
	return (0);
}

int	find_matches_wildcard(t_wildcard *match, char *s)
{
	size_t		i;
	char		*next;
	t_wildcard	new_match;
	t_lexer_tok	*match_tok;

	init_lexer(&new_match);
	i = 0;
	next = ft_strchr(s, '*');
	while (i < match->size)
	{
		match_tok = at_vector(match, i);
		if (ft_strncmp(match_tok->content, s, s - next) == 0)
		{
		}
		i++;
	}
	clear_lexer(match);
	*match = new_match;
	return (0);
}

int	add_match_tok(t_wildcard *matches)
{
	t_lexer_tok token;

	token.content = ft_strdup(s);
}

int	get_ls_vector(t_env *env, t_wildcard *matches)
{
	DIR				*dir;
	struct dirent	*entry;
	t_lexer_tok		token;
	char	*wd;

	wd = ms_getenv(env, "PWD");
	if (wd == NULL)
		return (dprintf(2, "minishell: ms_get_env error\n"), -1);
	dir = opendir(wd);
	if (dir == NULL)
		return (perror("opendir"), -1);
	entry = readdir(dir);
	while (entry != NULL)
	{
		token.content = ft_strdup(entry->d_name);
		if (token.content == NULL)
			return (-1);
		token.type = WORD;
		if (add_vector(matches, &token , 1) == -1)
			return (-1);
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}
