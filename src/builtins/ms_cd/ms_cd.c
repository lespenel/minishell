/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:59:18 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/08 02:06:42 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_io.h"
#include "ft_string.h"
#include "vector.h"
#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

static	char	*get_curpath(t_env *env, char *dir_operand);
static	int		set_pwd(t_env *env, char *curpath);

int	ms_cd(t_env	*env, char **args)
{
	char		*curpath;
	char		*dir_operand;

	dir_operand = get_dir_operand(env, args);
	if (dir_operand == NULL)
		return (1);
	curpath = get_curpath(env, dir_operand);
	if (curpath == NULL
		|| get_canonical_path(&curpath) == -1
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

static	int	set_pwd(t_env *env, char *curpath)
{
	if (ms_setenv(env, "PWD", curpath) == -1)
		return (-1);
	if (ms_setenv(env, "OLDPWD", curpath) == -1)
		return (-1);
	return (0);
}

static	char *get_wd(t_env *env)
{
	char	*wd;

	wd = ms_getenv(env, "PWD");
}

static	char *get_curpath(t_env *env, char *dir_operand)
{
	char	*curpath;
	char	*wd;

	(void)env;
	if (ft_strncmp(dir_operand, "/", 1) == 0)
		return (ft_strdup(dir_operand));
	else
	{
		wd = ms_getenv(env, "PWD");
		if (wd == NULL)
			wd = getcwd(NULL, 0);
		if (wd == NULL)
			return (NULL);


		if (wd[ft_strlen(wd) - 1] == '/')
			curpath = ft_strjoin(wd, dir_operand);
		else
			curpath = ft_strjoin_three(wd, "/", dir_operand);
	}
	return (curpath);
}
