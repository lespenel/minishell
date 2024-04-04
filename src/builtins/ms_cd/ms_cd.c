/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:59:18 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/04 08:07:10 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_io.h"
#include "ft_string.h"
#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

static	char *get_curpath(t_env *env, char *dir_operand);
static	int	set_pwd(t_env *env, char *curpath);

static	int	set_pwd(t_env *env, char *curpath)
{
	char	*wd;
	size_t	len;

	(void)curpath;
	wd = getcwd(NULL, 0);
	if (wd == NULL)
		return (-1);
	len = ft_strlen(wd);
	if (len > 1 && wd[len - 1] == '/')
		wd[len - 1] = '\0';
	if (ms_setenv(env, "PWD", wd) == -1)
	{
		free(wd);
		return (-1);
	}
	free(wd);
	return (0);
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
		wd = getcwd(NULL, 0);
		if (wd == NULL)
			return (NULL);
		if (wd[ft_strlen(wd) - 1] == '/')
			curpath = ft_strjoin(wd, dir_operand);
		else
			curpath = ft_strjoin_three(wd, "/", dir_operand);
		free(wd);
	}
	return (curpath);
}

int	ms_cd(t_env	*env, char **args)
{
	char		*curpath;
	char		*dir_operand;
	char		*wd;

	dir_operand = get_dir_operand(env, args);
	if (dir_operand == NULL)
		return (1);
	curpath = get_curpath(env, dir_operand);
	if (curpath == NULL)
	{
		free(dir_operand);
		return (1);
	}
	if (chdir(curpath) == -1
		|| set_pwd(env, curpath) == -1)
	{
		ft_dprintf(2, DIR_NOT_EXIST, dir_operand);
		free(dir_operand);
		free(curpath);
		return (1);
	}
	wd = ms_getenv(env, "PWD");
	ft_dprintf(2, "dir operand = %s\n", dir_operand);
	ft_dprintf(2, "curpath     = %s\n", curpath);
	ft_dprintf(2, "wd          = %s\n", wd);
	free(dir_operand);
	free(curpath);
	return (0);
}
