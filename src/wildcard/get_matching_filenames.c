/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matching_filenames.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 06:05:17 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 16:25:11 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include "wildcard.h"
#include <dirent.h>
#include <stdio.h>

int	compare_filenames(t_lexer *filenames, t_lexer *pattern, char *to_compare);

int	for_each_file(t_pattern *pattern, t_lexer *filenames)
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
		if (compare_filenames(&new_dir_lst, &pattern->pattern, tok->content) == -1)
			return (-1);
		print_lexer(filenames);
		++i;
	}
	clear_lexer(filenames);
	*filenames = new_dir_lst;
	return (0);
}

int	get_matching_filenames(t_wildcard *wildcard, t_lexer *filenames)
{
	t_pattern	*pattern;

	printf("patterns size = %ld\n", wildcard->patterns.size);
	pattern = at_vector(&wildcard->patterns, wildcard->patterns.size - 1);
	if (wildcard->patterns.size == 1)
	{
	printf("bite\n");
		if (compare_filenames(filenames, &pattern->pattern, NULL) == -1)
			return (-1);
	}
	else
	{
		if (for_each_file(pattern, filenames) == -1)
			return (-1);
	}
	return (0);
}

int	compare_filenames(t_lexer *filenames, t_lexer *pattern, char *to_compare)
{
	t_lexer		new_filenames;
	t_lexer_tok *match_tok;
	size_t		j;

	init_lexer(&new_filenames);
	j = 0;

	if (get_files_ls(&new_filenames, to_compare) == -1)
	{
		clear_lexer(&new_filenames);
		return (-1);
	}
	printf("first dir ls\n");
	print_lexer(&new_filenames);
	while (j < new_filenames.size)
	{
		match_tok = at_vector(&new_filenames, j);
		print_lexer(pattern);
		if (is_wildcard_match(pattern, match_tok->content) == 1)
		{
			if (add_dir_tok(filenames, match_tok->content, 0) == -1)
			{
				clear_lexer(&new_filenames);
				return (-1);
			}
		}
		++j;
	}
	return (0);
}
