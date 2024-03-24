/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:42:43 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 13:52:48 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "wildcard.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	add_file_tok(t_lexer *filenames, char *s, int directory)
{
	t_lexer_tok	token;

	if (ft_strcmp("..", s) == 0 || ft_strcmp(".", s) == 0)
		return (0);
	if (s[0] == '.')
		return (0);
	if (directory)
		token.content = ft_strjoin(s, "/");
	else
		token.content = ft_strdup(s);
	if (token.content == NULL)
		return (-1);
	if (directory)
		token.type = 5;
	else
		token.type = WORD;
	printf("file_tok content = %s\n", token.content);
	if (add_vector(filenames, &token, 1) == -1)
		return (-1);
	return (0);
}

int	get_files_ls(t_env *env, t_lexer *filenames)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*wd;

	(void)env;
	wd = getcwd(NULL, 0);
	if (wd == NULL)
		return (-1);
	dir = opendir(wd);
	if (dir == NULL)
	{
		perror("opendir");
		return (-1);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (add_file_tok(filenames, entry->d_name, 0) == -1)
		{
			closedir(dir);
			return (-1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}
