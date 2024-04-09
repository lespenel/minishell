/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:59:18 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/10 00:24:42 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/ms_cd.h"
#include <stdlib.h>

int	ms_cd(t_env	*env, char **args)
{
	char		*curpath;
	char		*dir_operand;

	dir_operand = get_dir_operand(env, args);
	if (dir_operand == NULL)
		return (1);
	curpath = get_curpath(env, dir_operand);
	if (curpath == NULL
		|| get_canonical_path(env, &curpath, dir_operand) == -1
		|| change_directory(env, &curpath, dir_operand) == -1)
	{
		free(dir_operand);
		free(curpath);
		return (1);
	}
	free(dir_operand);
	free(curpath);
	return (0);
}
