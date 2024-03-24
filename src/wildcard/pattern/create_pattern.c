/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pattern.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 06:57:29 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 13:00:49 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "util.h"
#include "wildcard.h"

static int	get_dir_nb(t_lexer *first_pattern);
static int	split_pattern(t_wildcard *wildcard, t_lexer *first_pattern);

int	create_pattern(t_wildcard *wildcard, char *raw_pattern)
{
	t_lexer	first_pattern;

	if (fill_pattern(&first_pattern, raw_pattern) == -1
		|| remove_backslash(&first_pattern) == -1)
	{
		clear_lexer(&first_pattern);
		return (-1);
	}
	print_lexer(&first_pattern);
	wildcard->nb_dir = get_dir_nb(&first_pattern);
	if (split_pattern(wildcard, &first_pattern) == -1)
	{
		clear_lexer(&first_pattern);
		return (-1);
	}
	return (0);
}

static int	split_pattern(t_wildcard *wildcard, t_lexer *first_pattern)
{
	int			i;
	int			nb_dir;
	int			ret;

	i = 0;
	nb_dir = wildcard->nb_dir;
	while (nb_dir)
	{
		ret = create_dir_pattern(wildcard, first_pattern, i);
		if (ret == -1)
			return (-1);
		i += ret;
		--nb_dir;
	}
	if (add_file_pattern(wildcard, first_pattern, i) == -1)
		return (-1);
	clear_vector(first_pattern);
	return (0);
}

static int	get_dir_nb(t_lexer *first_pattern)
{
	size_t		i;
	size_t		nb_dir;
	t_lexer_tok	*tok;

	i = 0;
	nb_dir = 0;
	while (i < first_pattern->size)
	{
		tok = at_vector(first_pattern, i);
		if (tok->type == WORD)
		{
			if (ms_strchr(tok->content, '/'))
				++nb_dir;
		}
		++i;
	}
	return (nb_dir);
}
