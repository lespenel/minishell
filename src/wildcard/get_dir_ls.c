/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:59:06 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/28 09:36:59 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "wildcard.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

static int	is_dir(t_wild *wildcard, char *d_name, char *path);
static int	cmp_dir(t_wild *w, t_lexer *pattern, struct dirent *dir, char *s);

int	get_dir_ls(t_wild *w, t_lexer *pattern, t_lexer *filenames, char *path)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = get_dir_path(w, path);
	if (dir == NULL)
		return (0);
	w->f_lst_ptr = filenames;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (cmp_dir(w, pattern, entry, path) == -1)
		{
			closedir(dir);
			return (-1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

static int	cmp_dir(t_wild *w, t_lexer *patt, struct dirent *dir, char *path)
{
	char	*tmp;

	tmp = ft_strjoin(dir->d_name, "/");
	if (tmp == NULL)
		return (-1);
	if (is_dir(w, tmp, path) && is_wildcard_match(w, patt, tmp)
		&& compare_globignore(w, tmp))
	{
		if (path)
		{
			free(tmp);
			tmp = ft_strjoin_three(path, dir->d_name, "/");
			if (tmp == NULL)
				return (-1);
		}
		if (add_file_tok(w->f_lst_ptr, tmp) == -1)
		{
			free(tmp);
			return (-1);
		}
	}
	free(tmp);
	return ((errno == 0) - 1);
}

static int	is_dir(t_wild *wildcard, char *d_name, char *path)
{
	struct stat	*buff;
	char		*path_for_stat;
	int			ret;

	buff = malloc(sizeof(struct stat));
	if (buff == NULL)
		return (-1);
	if (path)
		path_for_stat = ft_strjoin_three(wildcard->wd, path, d_name);
	else
		path_for_stat = ft_strjoin(wildcard->wd, d_name);
	if (path_for_stat == NULL)
	{
		free(buff);
		return (-1);
	}
	if (stat(path_for_stat, buff) < 0)
		ret = 0;
	else
		ret = S_ISDIR(buff->st_mode);
	errno = 0;
	free(path_for_stat);
	free(buff);
	return (ret);
}
