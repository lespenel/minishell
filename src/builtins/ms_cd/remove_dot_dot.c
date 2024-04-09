/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dot_dot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 01:48:30 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 08:05:19 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include "ft_io.h"
#include "vector.h"
#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static	int		check_short_path(t_env *env, char *path);
static	int		is_directory(t_env *env, char *path, char *dir_operand);
static	void	remove_before_dir(t_vector *n_path);

int	remove_dot_dot(t_env *env, t_vector *n_path, t_vector *s_path, char *dir_op)
{
	char	**curr;
	size_t	i;

	i = 0;
	while (i < s_path->size)
	{
		curr = at_vector(s_path, i);
		if (ft_strcmp(*curr, ".."))
		{
			if (add_vector(n_path, *curr, ft_strlen(*curr)) == -1
				|| add_vector(n_path, "/", 1) == -1
				|| is_directory(env, n_path->array, dir_op) == 0)
				return (-1);
			++i;
		}
		else 
		{
			free(*curr);
			remove_vector(s_path, i);
			remove_before_dir(n_path);
		}
	}
	return (0);
}

static	void	remove_before_dir(t_vector *n_path)
{
	size_t	i;
	char	*curr;
	size_t	n_len;

	i = 0;
	n_len = 1;
	if (n_path->size == 1)
		return ;
	curr = at_vector(n_path, n_path->size - 1 - n_len);
	while (*curr != '/')
	{
		++n_len;
		curr = at_vector(n_path, n_path->size - 1 - n_len);
	}
	while (i < n_len)
	{
		remove_vector(n_path, n_path->size - 1);
		++i;
	}
}

static	int	is_directory(t_env *env, char *path, char *dir_operand)
{
	struct stat buff;
	int	ret;

	if (stat(path, &buff) < 0)
		ret = 0;
	else
		ret = S_ISDIR(buff.st_mode);
	if (ret == 0 && errno == 36)
	{
		errno = 0;
		ret = check_short_path(env, path);
	}
	if (ret == 0 && errno == 36)
	{
		ft_dprintf(2, "GROSCHIBRE\n");
		ft_dprintf(2, FILENAME_TO_LONG, dir_operand);
	}
	else if (ret == 0)
		ft_dprintf(2, NO_SUCH_FILE, dir_operand);
	return (ret);
}

static	int	check_short_path(t_env *env, char *path)
{
	struct stat buff;
	char	*wd;
	size_t	wd_len;

	wd = get_wd(env);
	if (wd == NULL)
		return (0);
	wd_len = ft_strlen(wd);
	printf("path_len = %ld", ft_strlen(path + wd_len + 1));
	if (ft_strncmp(path, wd, wd_len) == 0)
	{
		if (stat(path + wd_len + 1, &buff) < 0)
		{
			printf("%d\n", PATH_MAX);
			if (ft_strlen(path + wd_len + 1) == PATH_MAX)
				return (printf("lol\n"), 1);
			printf("AlainSoral le bo$$\n");
			free(wd);
			return (0);
		}
	}
	free(wd);
	return (S_ISDIR(buff.st_mode));
}
