/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 04:13:43 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 11:35:05 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"
#include "ft_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static	int	set_pwd(t_env *env, char *curpath);

int	change_directory(t_env *env, char **curpath, char *dir_operand)
{
	int		ret;
	char	*wd;
	char	*tmp;

	ret = check_path_size(env, curpath, dir_operand);
	if (ret == -1)
		return (-1);
	if (chdir(*curpath) == -1)
		return (-1);
	if (ret == 1)
	{
		wd = get_wd(env);
		if (wd == NULL)
			return (-1);
		tmp = ft_strjoin_three(wd, "/", *curpath);
		free(wd);
		if (tmp == NULL)
			return (-1);
		free(*curpath);
		*curpath = tmp;
		printf("lol\n");
	}
	if (set_pwd(env, *curpath) == -1)
		return (1);
	return (0);
}

static	int	set_pwd(t_env *env, char *curpath)
{
	char	*wd;

	wd = get_wd(env);
	if (wd != NULL)
	{
		if (ms_setenv(env, "OLDPWD", wd) == -1)
		{
			free(wd);
			return (-1);
		}
		free(wd);
	}
	if (ms_setenv(env, "PWD", curpath) == -1)
		return (-1);
	return (0);
}
