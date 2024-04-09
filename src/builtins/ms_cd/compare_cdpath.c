/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_cdpath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:55:46 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 11:42:39 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static char		*get_cdpath(t_env *env);
static char		*is_dir_in_cdpath(char *cdpath, char *dir_operand);
static int		is_directory(char *path);
static char		*get_full_path(t_env *env, char *curpath);

char	*compare_cdpath(t_env *env, char *dir_operand)
{
	char	*cdpath;
	char	*curpath;

	if (ft_strncmp(dir_operand, "..", 2) == 0
		|| ft_strncmp(dir_operand, ".", 1) == 0)
		return (NULL);
	cdpath = get_cdpath(env);
	if (cdpath == NULL)
		return (NULL);
	curpath = is_dir_in_cdpath(cdpath, dir_operand);
	free(cdpath);
	if (curpath)
		curpath = get_full_path(env, curpath);
	return (curpath);
}

static char	*is_dir_in_cdpath(char *cdpath, char *dir_operand)
{
	char	*tok;
	char	*curpath;

	curpath = NULL;
	tok = cd_strtok(cdpath, ":");
	while (tok)
	{
		printf("tok = %s\n", tok);
		if (*tok == '\0')
			curpath = ft_strjoin("./", dir_operand);
		else if (tok[ft_strlen(tok) - 1] == '/')
			curpath = ft_strjoin(tok, dir_operand);
		else
			curpath = ft_strjoin_three(tok, "/", dir_operand);
		if (curpath == NULL)
			return (NULL);
		if (is_directory(curpath))
			break ;
		free(curpath);
		tok = cd_strtok(NULL, ":");
	}
	return (curpath);
}

static char	*get_cdpath(t_env *env)
{
	char	*cdpath;

	cdpath = ms_getenv(env, "CDPATH");
	if (cdpath == NULL)
		return (NULL);
	cdpath = ft_strdup(cdpath);
	return (cdpath);
}

static int	is_directory(char *path)
{
	struct stat	buff;
	int			ret;

	if (stat(path, &buff) < 0)
		ret = 0;
	else
		ret = S_ISDIR(buff.st_mode);
	errno = 0;
	return (ret);
}

static char	*get_full_path(t_env *env, char *curpath)
{
	char	*n_curpath;
	char	*wd;

	wd = get_wd(env);
	if (wd == NULL)
		return (NULL);
	if (curpath[0] == '/')
		n_curpath = ft_strjoin(wd, curpath);
	else
		n_curpath = ft_strjoin_three(wd, "/", curpath);
	free(wd);
	if (n_curpath == NULL)
		return (NULL);
	free(curpath);
	return (n_curpath);
}
