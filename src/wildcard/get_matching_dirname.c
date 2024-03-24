/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matching_dirname.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:23:45 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 20:45:02 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include "wildcard.h"
#include <stdio.h>

int	compare_dir(char *gignore, t_lexer *fnames, t_lexer *pattern, char *to_comp);

int	for_each_dir(char *gignore, t_pattern *pattern, t_lexer *filenames)
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
		if (compare_dir(gignore, &new_dir_lst, &pattern->pattern, tok->content) == -1)
			return (-1);
		print_lexer(filenames);
		++i;
	}
	clear_lexer(filenames);
	*filenames = new_dir_lst;
	return (0);
}

int	get_matching_dirname(t_wildcard *wild, t_lexer *filenames, int nb_dir)
{
	t_pattern	*pattern;

	if (nb_dir == wild->nb_dir || wild->nb_dir == 0)
		return (0);
	pattern = at_vector(&wild->patterns, nb_dir);
	if (nb_dir == 0)
	{
		if (compare_dir(wild->globignore, filenames,
			&pattern->pattern, NULL) == -1)
			return (-1);
	}
	else if (for_each_dir(wild->globignore, pattern, filenames) == -1)
		return (-1);
	return (get_matching_dirname(wild, filenames, nb_dir + 1));
}

int	compare_dir(char *gignore, t_lexer *fnames, t_lexer *pattern, char *to_comp)
{
	t_lexer		new_filenames;
	t_lexer_tok *match_tok;
	size_t		j;

	init_lexer(&new_filenames);
	j = 0;

	if (get_dir_ls(&new_filenames, to_comp) == -1)
	{
		clear_lexer(&new_filenames);
		return (-1);
	}
	printf("first dir ls\n");
	print_lexer(&new_filenames);
	while (j < new_filenames.size)
	{
		match_tok = at_vector(&new_filenames, j);
		if (is_wildcard_match(gignore, pattern, match_tok->content) == 1)
		{
			if (add_file_tok(fnames, match_tok->content) == -1)
			{
				clear_lexer(&new_filenames);
				return (-1);
			}
		}
		++j;
	}
	return (0);
}
