/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_curpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 05:16:39 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 11:39:31 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include <errno.h>
#include <stdlib.h>

char	*get_curpath(t_env *env, char *dir_operand)
{
	char	*curpath;
	char	*wd;

	if (ft_strncmp(dir_operand, "/", 1) == 0)
		return (ft_strdup(dir_operand));
	curpath = compare_cdpath(env, dir_operand);
	if (curpath)
		return (curpath);
	else if (errno)
		return (NULL);
	else
	{
		wd = get_wd(env);
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
