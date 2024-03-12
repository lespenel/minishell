/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wildcard_match.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:11:46 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/12 09:08:39 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "ft_string.h"
#include <stdio.h>

static int	compare_pattern(t_lexer *pattern, char *f_name);
static int	is_pair_match(t_lexer_tok *t1, t_lexer_tok *t2, char *fname, int n);
static int	compare_termination(char *f_name, char *to_find);

int	is_wildcard_match(char *motif, char *f_name)
{
	t_lexer	pattern;

	if (ft_strcmp(f_name, ".") == 0)
		return (0);
	if (ft_strcmp(f_name, "..") == 0)
		return (0);
	if (motif[0] != '.' && f_name[0] == '.')
		return (0);
	if (fill_pattern(&pattern, motif) == -1)
	{
		clear_lexer(&pattern);
		return (-1);
	}
	print_lexer(&pattern);
	if (pattern.size == 1)
		return (0);
	if (compare_pattern(&pattern, f_name) == 1)
	{
		clear_lexer(&pattern);
		return (1);
	}
	clear_lexer(&pattern);
	return (0);
}

static int	compare_pattern(t_lexer *pattern, char *f_name)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	if (pattern->size == 1)
		return (0);
	token = at_vector(pattern, i);
	if (pattern->size == 2 && token->type == WORD)
		return (0);
	while (i < pattern->size - 1)
	{
		if (is_pair_match(token, at_vector(pattern, i + 1), f_name, i) == 0)
			return (0);
		++i;
		token = at_vector(pattern, i);
	}
	return (1);
}

static int	is_pair_match(t_lexer_tok *t1, t_lexer_tok *t2, char *fname, int n)
{
	if (t1->type == 0 && t2->type == NEWLINE)
		return (1);
	else if (t1->type == 0 && t2->type != NEWLINE)
		return (ft_strnstr(fname, t2->content, ft_strlen(fname)) != 0);
	else if (t1->type == WORD && t2->type == NEWLINE)
	{
		if (compare_termination(fname, t1->content) == 0)
			return (1);
	}
	else if (t1->type == WORD && t2->type != NEWLINE && n == 0)
	{
		if (ft_strncmp(t1->content, fname, ft_strlen(t1->content)) == 0)
			return (1);
	}
	else if (t1->type == WORD && t2->type != NEWLINE)
	{
		return (1);
	}
	return (0);
}

static int	compare_termination(char *f_name, char *to_find)
{
	ssize_t	file_l;
	ssize_t	find_l;
	ssize_t	i;

	i = 0;
	file_l = ft_strlen(f_name);
	find_l = ft_strlen(to_find);
	if (file_l < find_l)
		return (1);
	while (i != find_l && f_name[file_l - i - 1] == to_find[find_l - i - 1])
		i++;
	return (i != find_l);
}
