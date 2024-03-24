/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:42:43 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 16:10:23 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "wildcard.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	add_file_tok(t_lexer *filenames, char *s)
{
	t_lexer_tok	token;

	token.content = ft_strdup(s);
	if (token.content == NULL)
		return (-1);
	token.type = WORD;
	if (add_vector(filenames, &token, 1) == -1)
		return (-1);
	return (0);
}

int	get_files_ls(t_lexer *filenames, char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*wd;

	wd = getcwd(NULL, 0);
	if (wd == NULL)
		return (-1);
	if (path)
	{
		wd = ft_strjoin_three(wd, "/", path);
		if (wd == NULL)
			return (-1);
	}
	dir = opendir(wd);
	if (dir == NULL)
	{
		perror("opendir");
		return (-1);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (add_file_tok(filenames, entry->d_name) == -1)
		{
			closedir(dir);
			return (-1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}
