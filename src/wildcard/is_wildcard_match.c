/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wildcard_match.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:11:46 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/16 14:06:56 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "wildcard.h"
#include <stdlib.h>

static int	compare_pattern_filenames(t_lexer *pattern, char *f_name);
static char	*midlle_pattern(t_lexer *pattern, char *f_name);
static int	hidden_file(t_lexer *pattern, char *f_name, char *gignore);

int	is_wildcard_match(t_wild *wild, t_lexer *pattern, char *f_name)
{
	if (pattern->size == 0)
		return (0);
	if (hidden_file(pattern, f_name, wild->globignore) == 0)
		return (0);
	if (compare_pattern_filenames(pattern, f_name) == 1)
		return (1);
	return (0);
}

static int	hidden_file(t_lexer *pattern, char *f_name, char *globignore)
{
	t_lexer_tok	*tok;

	tok = at_vector(pattern, 0);
	if (globignore)
		return (1);
	if (f_name[0] == '.' && tok->content[0] != '.')
		return (0);
	return (1);
}

static int	compare_pattern_filenames(t_lexer *pattern, char *f_name)
{
	t_lexer_tok	*tok;
	size_t		len;

	tok = at_vector(pattern, 0);
	if (tok->type == WORD)
	{
		if (pattern->size == 1)
			return (ft_strcmp(f_name, tok->content) == 0);
		len = ft_strlen(tok->content);
		if (ft_strncmp(tok->content, f_name, len))
			return (0);
		f_name += len;
	}
	if (pattern->size == 1)
		return (1);
	f_name = midlle_pattern(pattern, f_name);
	if (f_name == NULL)
		return (0);
	tok = at_vector(pattern, pattern->size - 1);
	if (tok->type == 0)
		return (1);
	if (check_end_pattern(tok->content, f_name) == 1)
		return (1);
	return (0);
}

static char	*midlle_pattern(t_lexer *pattern, char *f_name)
{
	size_t		i;
	t_lexer_tok	*tok;
	char		*ret;

	i = 1;
	while (i < pattern->size - 1)
	{
		tok = at_vector(pattern, i);
		if (tok->type == WORD)
		{
			ret = ft_strnstr(f_name, tok->content, ft_strlen(f_name));
			if (ret == NULL)
				return (NULL);
			f_name = ret + ft_strlen(tok->content);
		}
		++i;
	}
	return (f_name);
}
