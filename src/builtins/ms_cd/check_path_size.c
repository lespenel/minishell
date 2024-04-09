/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 03:45:57 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 11:35:44 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "builtins.h"
#include "ft_string.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

static	int	compare_path_max(size_t	path_len, size_t wd_len);

int	check_path_size(t_env *env, char **curpath, char *dir_operand)
{
	const size_t	path_len = ft_strlen(*curpath) + 1;
	char			*wd;
	char			*tmp;

	if (path_len <= PATH_MAX)
		return (0);
	wd = get_wd(env);
	if (wd == NULL)
		return (-1);
	if (compare_path_max(path_len, ft_strlen(wd)) == 0)
	{
		free(wd);
		ft_dprintf(2, FILENAME_TO_LONG, dir_operand);
		return (-1);
	}
	if (ft_strncmp(*curpath, wd, ft_strlen(wd)) == 0)
	{
		tmp = ft_strdup(*curpath + ft_strlen(wd) + 1);
		free(wd);
		if (tmp == NULL)
			return (-1);
		free(*curpath);
		*curpath = tmp;
		return (1);
	}
	free(wd);
	return (-1);
}

static	int	compare_path_max(size_t	path_len, size_t wd_len)
{
	if (PATH_MAX < wd_len)
		return (0);
	if (wd_len >= path_len)
		return (1);
	if (PATH_MAX < path_len - wd_len - 1)
		return (0);
	return (1);
}
