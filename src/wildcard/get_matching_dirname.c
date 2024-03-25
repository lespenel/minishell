/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matching_dirname.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:23:45 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/25 05:32:21 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include "wildcard.h"
#include <stdio.h>

int	for_each_dir(t_wildcard *wild, t_pattern *pattern, t_lexer *filenames);

int	get_matching_dirname(t_wildcard *wild, t_lexer *filenames, int nb_dir)
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

int	for_each_dir(t_wildcard *wild, t_pattern *pattern, t_lexer *filenames)
{
	t_lexer_tok	*tok;
	size_t		i;
	size_t		old_size;
	t_lexer		new_dir_lst; 

	i = 0;
	old_size = filenames->size;
	init_lexer(&new_dir_lst);
	while (i < old_size)
	{
	  	tok = at_vector(filenames, i);
		if (get_dir_ls(wild, &pattern->pattern, &new_dir_lst, tok->content) == -1)
			return (-1);
		print_lexer(filenames);
		++i;
	}
	clear_lexer(filenames);
	*filenames = new_dir_lst;
	return (0);
}
