/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:59:06 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 15:30:13 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "wildcard.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	add_dir_tok(t_lexer *filenames, char *s, int directory)
{
	t_lexer_tok	token;

	if (directory)
		token.content = ft_strjoin(s, "/");
	else
		token.content = ft_strdup(s);
	if (token.content == NULL)
		return (-1);
	token.type = WORD;
	if (directory)
		printf("file_tok content = %s\n", token.content);
	if (add_vector(filenames, &token, 1) == -1)
		return (-1);
	return (0);
}
int	get_dir_ls(t_lexer *filenames, char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	char 			*wd;

	wd = getcwd(NULL, 0);
	if (wd == NULL)
		return (-1);
	if (path)
	{
		wd = ft_strjoin_three(wd, "/", path);
		if (wd == NULL)
			return (-1);
	}
	printf("wd = %s\n", wd);
	dir = opendir(wd);
	if (dir == NULL)
		return (printf("opendir fail\n"), -1);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == 4)
		{
			printf("dname = %s\n", entry->d_name);
			if (path)
			{
				if (entry->d_name[0] != '.')
					add_dir_tok(filenames, ft_strjoin(path, entry->d_name), 1);
			}
			else if (add_dir_tok(filenames, entry->d_name, 1) == -1)
			{
				closedir(dir);
				return (-1);
			}
		}
		entry = readdir(dir);
	}
	print_lexer(filenames);
	closedir(dir);
	return (0);
}
