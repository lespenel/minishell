/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:59:18 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/08 05:48:17 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_io.h"
#include "ft_string.h"
#include <linux/limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static	int	set_pwd(t_env *env, char *curpath);
static	int	check_path_size(t_env *env, char **curpath);

int	ms_cd(t_env	*env, char **args)
{
	char		*curpath;
	char		*dir_operand;

	dir_operand = get_dir_operand(env, args);
	if (dir_operand == NULL)
		return (1);
	curpath = get_curpath(env, dir_operand);
	ft_dprintf(2, "currpath   = %s\n", curpath);
	if (curpath == NULL
		|| get_canonical_path(&curpath) == -1
		|| check_path_size(env, &curpath) == -1
		|| chdir(curpath) == -1
		|| set_pwd(env, curpath) == -1)
	{
		ft_dprintf(2, DIR_NOT_EXIST, dir_operand);
		free(dir_operand);
		free(curpath);
		return (1);
	}
	ft_dprintf(2, "canonical   = %s\n", curpath);
	free(dir_operand);
	free(curpath);
	return (0);
}
#include <stdio.h>
static	int	check_path_size(t_env *env, char **curpath)
{
	const size_t len = ft_strlen(*curpath) + 1;
	char		*wd;
	char		*tmp;

	if (len <= 5)
		return (0);
	wd = get_wd(env);
	if (wd == NULL)
		return (-1);
	if (PATH_MAX < (len - ft_strlen(wd)))
	{
		ft_dprintf(1, "bite\n");
		dprintf(1, "len = %lu\n", len - ft_strlen(wd));
		free(wd);
		return (-1);
	}
	if (ft_strncmp(*curpath, wd, ft_strlen(wd)) == 0)
	{
		tmp = ft_strdup(*curpath + ft_strlen(wd));
		free(wd);
		if (tmp == NULL)
			return (-1);
		free(*curpath);
		*curpath = tmp;
		return (0);
	}
	free(wd);
	return (-1);
}

static	int	set_pwd(t_env *env, char *curpath)
{
	if (ms_setenv(env, "PWD", curpath) == -1)
		return (-1);
	if (ms_setenv(env, "OLDPWD", curpath) == -1)
		return (-1);
	return (0);
}
