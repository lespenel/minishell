/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/14 06:33:22 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include "wildcard.h"
#include <stdlib.h>

static ssize_t	add_filename_lexer(t_lexer *lex, t_lexer *fnames, ssize_t i);

int	expand_wildcards(t_env *env, t_lexer *lexer)
{
	size_t		i;
	ssize_t		ret;
	t_lexer		file_names;
	t_lexer_tok	*token;

	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == WORD && ft_strchr(token->content, '*'))
		{
			if (get_matching_filenames(env, &file_names, token) == -1)
				return (-1);
			ret = add_filename_lexer(lexer, &file_names, i);
			if (ret == -1)
				return (-1);
			i += ret;
		}
		++i;
	}
	return (0);
}

static ssize_t	add_filename_lexer(t_lexer *lex, t_lexer *fnames, ssize_t i)
{
	t_lexer_tok	*token;

	if (fnames->size > 0)
	{
		token = at_vector(lex, i);
		free(token->content);
		remove_vector(lex, i);
		if (merge_vector(lex, fnames, i) == -1)
		{
			clear_lexer(fnames);
			return (-1);
		}
		i += fnames->size - 1;
		clear_vector(fnames);
	}
	return (i);
}
