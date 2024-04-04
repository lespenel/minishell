/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:42:43 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/05 00:22:39 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "wildcard.h"
#include <stdlib.h>

static int	cmp_file(t_wild *w, t_lexer *patt, struct dirent *dir, char *path);

int	get_files_ls(t_wild *w, t_lexer *pattern, t_vector *fname, char *path)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = get_dir_path(w, path);
	if (dir == NULL)
		return (0);
	w->f_lst_ptr = fname;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (cmp_file(w, pattern, entry, path) == -1)
		{
			closedir(dir);
			return (-1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

static int	cmp_file(t_wild *w, t_lexer *patt, struct dirent *dir, char *path)
{
	char	*tmp;

	if (is_wildcard_match(w, patt, dir->d_name)
		&& compare_globignore(w, dir->d_name))
	{
		tmp = dir->d_name;
		if (path)
		{
			tmp = ft_strjoin(path, dir->d_name);
			if (tmp == NULL)
				return (-1);
		}
		if (add_file_tok(w->f_lst_ptr, tmp) == -1)
		{
			return (-1);
		}
		if (path)
			free(tmp);
	}
	return (0);
}
