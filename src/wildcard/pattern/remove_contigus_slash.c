/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_contigus_slash.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 03:25:09 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/15 05:53:55 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include "wildcard.h"
#include <stdlib.h>

static int	copy_without_contigus_slash(t_lexer_tok *tok);
static void	remove_contigus_slash_in_pattern(t_lexer *lexer);

int	remove_contigus_slash(t_lexer *lexer)
{
	t_lexer_tok	*curr;
	size_t		i;

	i = 0;
	while (i < lexer->size)
	{
		curr = at_vector(lexer, i);
		if (curr->type == WORD)
		{
			if (copy_without_contigus_slash(curr) == -1)
				return (-1);
		}
		++i;
	}
	remove_contigus_slash_in_pattern(lexer);
	return (0);
}

static int	copy_without_contigus_slash(t_lexer_tok *tok)
{
	t_vector	new_s;
	size_t		i;

	i = 0;
	init_vector(&new_s, sizeof(char));
	while (tok->content[i])
	{
		if (tok->content[i] == '/')
		{
			while (tok->content[i] == '/')
				++i;
			--i;
		}
		if (add_vector(&new_s, tok->content + i, 1) == -1)
		{
			clear_vector(&new_s);
			return (-1);
		}
		++i;
	}
	free(tok->content);
	tok->content = new_s.array;
	return (0);
}

static void	remove_contigus_slash_in_pattern(t_lexer *lexer)
{
	size_t		i;
	t_lexer_tok	*curr;
	t_lexer_tok	*curr2;

	i = 0;
	while (i < lexer->size - 1)
	{
		curr = at_vector(lexer, i);
		curr2 = at_vector(lexer, i + 1);
		if (curr->type == WORD && curr2->type == WORD)
		{
			if (check_end_pattern("/", curr->content)
				&& check_end_pattern("/", curr2->content)
				&& ft_strlen(curr2->content) == 1)
			{
				free(curr2->content);
				remove_vector(lexer, i + 1);
				--i;
			}
		}
		++i;
	}
}
