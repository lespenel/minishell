/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:42:43 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/26 05:28:37 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "wildcard.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	is_file(char *s)
{
	if (ft_strcmp(s, ".") == 0)
		return (0);
	if (ft_strcmp(s, "..") == 0)
		return (0);
	return (1);
}

int	add_file_tok(t_lexer *filenames, char *s)
{
	t_lexer_tok	token;

	if (ft_strcmp(s, ".") == 0 || ft_strcmp(s, "..") == 0)
		return (0);
	token.content = ft_strdup(s);
	if (token.content == NULL)
		return (-1);
	token.type = WORD;
	if (add_vector(filenames, &token, 1) == -1)
		return (-1);
	return (0);
}

int	get_files_ls(t_wildcard *w, t_lexer *pattern, t_lexer *fname, char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*tmp;

	dir = get_dir_path(w, path);
	if (dir == NULL)
		return (0);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (is_file(entry->d_name) && is_wildcard_match(w, pattern, entry->d_name) &&
		compare_globignore(w, entry->d_name))
		{
			tmp = entry->d_name;
			if (path)
			{
				tmp = ft_strjoin(path, entry->d_name);
				if (tmp == NULL)
					return (-1);
			}
			if (add_file_tok(fname, tmp) == -1)
			{
				closedir(dir);
				return (-1);
			}
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}
