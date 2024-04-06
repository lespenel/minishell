/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_canonical_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:25:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/06 06:59:41 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "ft_string.h"
#include "sys/types.h"
#include "vector.h"
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static	void	remove_before_dir(t_vector *n_path, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		printf("%ld\n", i);
		remove_vector(n_path, n_path->size - 1);
		++i;
	}
	printf("size = %ld\n", n_path->size);
	printf("sortie remove = %s\n", (char *)n_path->array);
}

static	int	is_directory(char *path);
static	int	remove_dots(t_vector *split_path);
static	int	remove_dots_dots(t_vector *vector, t_vector *split_path)
{
	char	**curr;
	size_t	old_len;
	size_t	i;

	i = 0;
	old_len = 0;
	while (i < split_path->size)
	{
		curr = at_vector(split_path, i);
		if (ft_strcmp(*curr, ".."))
		{
			old_len = ft_strlen(*curr);
			if (add_vector(vector, *curr, old_len) == -1
				|| add_vector(vector, "/", 1) == -1)
				return (-1);
			if (is_directory(vector->array) == 0)
				return (1);
			++i;
		}
		else if (ft_strcmp(*curr, "..") == 0) 
		{
			printf("bite\n");
			free(*curr);
			remove_vector(split_path, i);
			if (old_len)
				remove_before_dir(vector, old_len + 1);
		}
	}
	return (0);
}

int		get_canonical_path(char **curpath)
{
	t_vector	new;
	t_vector	split;

	init_vector(&new, sizeof(char));
	init_vector(&split, sizeof(char *));
	if (add_vector(&new, "/", 1) == -1
		|| ft_split_vector(&split, *curpath, '/') == -1
		|| remove_dots(&split) == -1
	|| remove_dots_dots(&new, &split) == -1)
	{
		clear_vector(&split);
		clear_vector(&new);
		return (-1);
	}
	clear_vector(&split);
	free(*curpath);
	*curpath = ft_strdup(new.array);
	clear_vector(&new);
	if (*curpath == NULL)
		return (-1);
	return (0);
}

static	int	remove_dots(t_vector *split_path)
{
	char	**curr;
	size_t	i;

	i = 0;
	while (i < split_path->size)
	{
		curr = at_vector(split_path, i);
		if (ft_strcmp(*curr, ".") == 0)
		{
			free(*curr);
			remove_vector(split_path, i);
		}
		else
			++i;
	}
	return (0);
}

static	int	is_directory(char *path)
{
	struct stat buff;
	int	ret;

	if (stat(path, &buff) < 0)
		ret = 0;
	else
		ret = S_ISDIR(buff.st_mode);
	return (ret);
}


/*
static	int	remove_dots(t_vector *vector, char *curpath)
{
	char		*tok;
	char		*old;

	old = NULL;
	tok = ft_strtok(curpath, "/");
	while (tok)
	{
		printf("tok = %s\n", tok);
		if (old && ft_strcmp(tok, "..") && ft_strcmp(old, "."))
		{
			if (add_vector(vector, old, ft_strlen(old)) == -1
				|| add_vector(vector, "/", 1) == -1)
				return (-1);
		}
		else if (ft_strcmp(tok, "..") == 0)
		{
			tok = ft_strtok(NULL, "/");
		}
		old = tok;
		tok = ft_strtok(NULL, "/");
	}
	if (old && ft_strcmp(old, "..") && ft_strcmp(old, "."))
	{
		if (add_vector(vector, old, ft_strlen(old)) == -1)
			return (-1);
	}
	return (0);
}*/
