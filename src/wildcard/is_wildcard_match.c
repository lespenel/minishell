/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wildcard_match.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:11:46 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/13 06:50:22 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include "wildcard.h"
#include "ft_string.h"
#include <stdio.h>

static int	compare_pattern(t_lexer *pattern, char *f_name);
static char	*midlle_pattern(t_lexer *pattern, char *f_name);
static int	check_end_pattern(char *f_name, char *to_find);
static int	hiden_file(char *raw_pattern, char *f_name);

int	is_wildcard_match(char *motif, char *f_name)
{
	t_lexer	pattern;

	if (hiden_file(motif, f_name) == 0)
		return (0);
	if (fill_pattern(&pattern, motif) == -1)
	{
		clear_lexer(&pattern);
		return (-1);
	}
	if (compare_pattern(&pattern, f_name) == 1)
	{
		clear_lexer(&pattern);
		return (-1);
	}
	clear_lexer(&pattern);
	return (0);
}

static int	hiden_file(char *raw_pattern, char *f_name)
{
	if (ft_strcmp(f_name, ".") == 0)
		return (0);
	if (ft_strcmp(f_name, "..") == 0)
		return (0);
	if (raw_pattern[0] != '.' && f_name[0] == '.')
		return (0);
	return (1);
}

static int	compare_pattern(t_lexer *pattern, char *f_name)
{
	t_lexer_tok	*tok;
	size_t		len;

	tok = at_vector(pattern, 0);
	if (pattern->size == 1)
		return (0);
	if (pattern->size == 2)
		return (tok->type == 0);
	if (tok->type == WORD)
	{
		len = ft_strlen(tok->content);
		if (ft_strncmp(tok->content, f_name, len))
			return (0);
		f_name += len;
	}
	f_name = midlle_pattern(pattern, f_name);
	if (f_name == NULL)
		return (0);
	tok = at_vector(pattern, pattern->size - 2);
	if (tok->type == 0)
		return (1);
	if (check_end_pattern(f_name, tok->content) == 1)
		return (1);
	return (0);
}

static char	*midlle_pattern(t_lexer *pattern, char *f_name)
{
	size_t		i;
	t_lexer_tok	*tok;
	char		*ret;

	i = 1;
	while (i < pattern->size - 2)
	{
		tok = at_vector(pattern, i);
		if (tok->type == WORD)
		{
			ret = ft_strnstr(f_name, tok->content, ft_strlen(f_name));
			if (ret == NULL)
				return (NULL);
			else
				f_name = ret;
		}
		++i;
	}
	return (f_name);
}

static int	check_end_pattern(char *f_name, char *to_find)
{
	ssize_t	file_l;
	ssize_t	find_l;
	ssize_t	i;

	i = 0;
	file_l = ft_strlen(f_name);
	find_l = ft_strlen(to_find);
	if (file_l < find_l)
		return (0);
	while (i != find_l && f_name[file_l - i - 1] == to_find[find_l - i - 1])
		i++;
	return (i == find_l);
}
