/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matching_filenames.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 06:05:17 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/25 23:29:50 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include "wildcard.h"
#include <dirent.h>
#include <stdio.h>

int	for_each_file(t_wildcard *wild, t_pattern *pattern, t_lexer *filenames);

int	for_each_file(t_wildcard *wild, t_pattern *pattern, t_lexer *filenames)
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
		if (get_files_ls(wild, &pattern->pattern, &new_dir_lst, tok->content) == -1)
			return (-1);
		++i;
	}
	clear_lexer(filenames);
	*filenames = new_dir_lst;
	return (0);
}

int	get_matching_filenames(t_wildcard *wildcard, t_lexer *filenames)
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
