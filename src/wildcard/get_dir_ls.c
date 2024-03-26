/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:59:06 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/26 05:23:18 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "wildcard.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	is_dir(struct dirent *entry)
{
	if (ft_strcmp(entry->d_name, ".") == 0)
		return (0);
	if (ft_strcmp(entry->d_name, "..") == 0)
		return (0);
	if (entry->d_type == 4 || entry->d_type == 10)
		return (1);
	return (0);
}

int	get_dir_ls(t_wildcard *w, t_lexer *pattern, t_lexer *filenames, char *path)
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
		tmp = ft_strjoin(entry->d_name, "/");
		if (tmp == NULL)
			return (-1);
		if (is_dir(entry) && is_wildcard_match(w, pattern, tmp)
			&& compare_globignore(w, tmp))
		{
			if (path)
			{
				free(tmp);
				tmp = ft_strjoin_three(path, entry->d_name, "/");
				if (path == NULL)
					return (-1);
			}
			if (add_file_tok(filenames, tmp) == -1)
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
