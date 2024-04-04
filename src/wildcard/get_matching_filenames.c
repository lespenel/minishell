/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matching_filenames.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 06:05:17 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/05 01:41:53 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static int	for_each_file(t_wild *wild, t_pattern *pattern, t_vector *fnames);

int	get_matching_filenames(t_wild *wildcard, t_vector *filenames)
{
	t_pattern	*pattern;

	pattern = at_vector(&wildcard->patterns, wildcard->patterns.size - 1);
	if (wildcard->patterns.size == 1)
	{
		if (get_files_ls(wildcard, &pattern->pattern, filenames, NULL) == -1)
			return (-1);
	}
	else if (for_each_file(wildcard, pattern, filenames) == -1)
		return (-1);
	return (0);
}

static int	for_each_file(t_wild *wild, t_pattern *pattern, t_vector *filenames)
{
	char		**s;
	size_t		i;
	size_t		old_size;
	t_vector	new_lst;

	i = 0;
	old_size = filenames->size;
	init_vector(&new_lst, sizeof(char *));
	while (i < old_size)
	{
		s = at_vector(filenames, i);
		if (get_files_ls(wild, &pattern->pattern, &new_lst, *s) == -1)
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
