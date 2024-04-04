/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matching_dirname.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:23:45 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/05 01:44:17 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include "wildcard.h"

static int	for_each_dir(t_wild *wild, t_pattern *pattern, t_vector *filenames);

int	get_matching_dirname(t_wild *wild, t_vector *filenames, size_t nb_dir)
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

static int	for_each_dir(t_wild *wild, t_pattern *pattern, t_vector *filenames)
{
	char		**tok;
	size_t		i;
	t_vector	new_lst;

	i = 0;
	init_vector(&new_lst, sizeof(char *));
	while (i < filenames->size)
	{
		tok = at_vector(filenames, i);
		if (get_dir_ls(wild, &pattern->pattern, &new_lst, *tok) == -1)
		{
			clear_vector(&new_lst);
			return (-1);
		}
		++i;
	}
	clear_vector(filenames);
	*filenames = new_lst;
	return (0);
}
