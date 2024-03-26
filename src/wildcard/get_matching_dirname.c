/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matching_dirname.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:23:45 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/26 07:18:31 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "wildcard.h"

static int	for_each_dir(t_wild *wild, t_pattern *pattern, t_lexer *filenames);

int	get_matching_dirname(t_wild *wild, t_lexer *filenames, size_t nb_dir)
{
	t_pattern	*pattern;

	if (nb_dir == wild->nb_dir || wild->nb_dir == 0)
		return (0);
	pattern = at_vector(&wild->patterns, nb_dir);
	if (nb_dir == 0)
	{
		if (get_dir_ls(wild, &pattern->pattern, filenames, NULL) == -1)
			return (-1);
	}
	else if (for_each_dir(wild, pattern, filenames) == -1)
		return (-1);
	return (get_matching_dirname(wild, filenames, nb_dir + 1));
}

static int	for_each_dir(t_wild *wild, t_pattern *pattern, t_lexer *filenames)
{
	t_lexer_tok	*tok;
	size_t		i;
	t_lexer		new_lst;

	i = 0;
	init_lexer(&new_lst);
	while (i < filenames->size)
	{
		tok = at_vector(filenames, i);
		if (get_dir_ls(wild, &pattern->pattern, &new_lst, tok->content) == -1)
		{
			clear_lexer(&new_lst);
			return (-1);
		}
		++i;
	}
	clear_lexer(filenames);
	*filenames = new_lst;
	return (0);
}
