/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:42:43 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 20:25:54 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "wildcard.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

DIR	*get_file_path(char *path);

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

int	get_files_ls(t_lexer *fname, char *path)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = get_file_path(path);
	if (dir == NULL)
	{
		perror("opendir");
		return (-1);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (is_file(entry->d_name) && path)
		{
			if (add_file_tok(fname, ft_strjoin(path, entry->d_name)) == -1)
				return (-1);
		}
		else if (is_file(entry->d_name) && add_file_tok(fname, entry->d_name) == -1)
		{
			closedir(dir);
			return (-1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

DIR	*get_file_path(char *path)
{
	char 			*wd;
	char			*new_wd;
	DIR				*dir;

	wd = getcwd(NULL, 0);
	if (wd == NULL)
		return (NULL);
	if (path)
	{
		new_wd = ft_strjoin_three(wd, "/", path);
		free(wd);
		if (new_wd == NULL)
			return (NULL);
	}
	else
		new_wd = wd;
	printf("wd = %s\n", new_wd);
	dir = opendir(new_wd);
	free(new_wd);
	return (dir);
}
