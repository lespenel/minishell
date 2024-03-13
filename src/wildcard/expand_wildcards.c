/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/13 07:30:16 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include "wildcard.h"
#include <stdlib.h>
#include <stdio.h>

int	expand_wildcards(t_env *env, t_lexer *lexer)
{
	size_t		i;
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
			print_lexer(&file_names);
			if (file_names.size > 0)
			{
				free(token->content);
				remove_vector(lexer, i);
				if (merge_vector(lexer, &file_names, i) == -1)
				{
					clear_lexer(&file_names);
					return (-1);
				}
				i += file_names.size - 1;
				clear_vector(&file_names);
			}
		}
		++i;
	}
	return (0);
}
