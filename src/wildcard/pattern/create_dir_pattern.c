/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dir_pattern.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:27:34 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/25 04:16:58 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "wildcard.h"
#include <stdio.h>
#include <stdlib.h>

static int	add_dirname_tok(t_lexer *pattern, t_lexer_tok *tok, ssize_t slash);
static int	split_dir_tok(t_lexer *pattern, t_lexer_tok *tok);
static int	fill_dir_pattern(t_pattern *pattern, t_lexer *old_pattern, int i);

int	create_dir_pattern(t_wildcard *wildcard, t_lexer *first_pattern, int i)
{
	t_pattern	pattern;
	int			ret;

	ft_memset(&pattern, 0, sizeof(t_pattern));
	init_lexer(&pattern.pattern);
	ret = fill_dir_pattern(&pattern, first_pattern, i);
	if (ret == -1)
	{
		clear_lexer(&pattern.pattern);
		return (-1);
	}
	if (add_vector(&wildcard->patterns, &pattern, 1) == -1)
	{
		clear_lexer(&pattern.pattern);
		return (-1);
	}
	return (ret);
}

static int	fill_dir_pattern(t_pattern *pattern, t_lexer *first_pattern, int i)
{
	t_lexer_tok	*tok;
	int			old_i;
	int			ret;

	tok = at_vector(first_pattern, i);
	old_i = i;
	while (ms_strchr(tok->content, '/') == NULL)
	{
		if (add_vector(&pattern->pattern, tok, 1) == -1)
			return (-1);
		++i;
		tok = at_vector(first_pattern, i);
	}
	ret = split_dir_tok(&pattern->pattern, tok);
	if (ret == -1)
		return (-1);
	pattern->type = DIRECTORY;
	return (ret + i - old_i);
}

static int	split_dir_tok(t_lexer *pattern, t_lexer_tok *tok)
{
	ssize_t			slash;
	char			*new_str;

	slash = 0;
	while (tok->content[slash] && tok->content[slash] != '/')
		++slash;
	if (tok->content[slash + 1] == '\0')
	{
		if (add_vector(pattern, tok, 1) == -1)
			return (-1);
		return (1);
	}
	if (add_dirname_tok(pattern, tok, slash) == -1)
		return (-1);
	new_str = ft_strdup(tok->content + slash + 1);
	if (new_str == NULL)
		return (-1);
	free(tok->content);
	tok->content = new_str;
	return (0);
}

static int	add_dirname_tok(t_lexer *pattern, t_lexer_tok *tok, ssize_t slash)
{
	t_lexer_tok		new_tok;

	new_tok.content = malloc(sizeof(char) * slash + 2);
	if (new_tok.content == NULL)
		return (-1);
	ft_strncpy(new_tok.content, tok->content, slash + 1);
	new_tok.content[slash + 1] = '\0';
	new_tok.type = WORD;
	if (add_vector(pattern, &new_tok, 1) == -1)
	{
		free(new_tok.content);
		return (-1);
	}
	return (0);
}
