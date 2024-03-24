/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:59:06 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 23:55:23 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "wildcard.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

DIR	*get_dir_path(t_wildcard *wild, char *path);

int	is_dir(struct dirent *entry)
{
	if (ft_strcmp(entry->d_name, ".") == 0)
		return (0);
	if (ft_strcmp(entry->d_name, "..") == 0)
		return (0);
	if (entry->d_type == 4)
		return (1);
	return (0);
}

int	add_dir_tok(t_lexer *filenames, char *s, int directory)
{
	t_lexer_tok	token;

	token.content = ft_strjoin(s, "/");
	if (token.content == NULL)
		return (-1);
	token.type = WORD;
	if (directory)
		printf("file_tok content = %s\n", token.content);
	if (add_vector(filenames, &token, 1) == -1)
		return (-1);
	return (0);
}
int	get_dir_ls(t_wildcard *wildcard, t_lexer *filenames, char *path)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = get_dir_path(wildcard, path);
	if (dir == NULL)
		return (-1);
	entry = readdir(dir);
	while (entry != NULL)
	{
		printf("dname = %s\n", entry->d_name);
		if (is_dir(entry) && path)
		{
			if (add_dir_tok(filenames, ft_strjoin(path, entry->d_name), 1) == -1)
				return (-1);
		}
		else if (is_dir(entry) && add_dir_tok(filenames, entry->d_name, 1) == -1)
		{
			closedir(dir);
				return (-1);
		}
		entry = readdir(dir);
	}
	print_lexer(filenames);
	closedir(dir);
	return (0);
}

DIR	*get_dir_path(t_wildcard *wild, char *path)
{
	char 			*wd;
	char			*new_wd;
	DIR				*dir;

	(void)wild;
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
