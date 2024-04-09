/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:59:18 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 11:42:49 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_io.h"
#include <stdlib.h>

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
		|| get_canonical_path(env, &curpath, dir_operand) == -1
		|| change_directory(env, &curpath, dir_operand) == -1)
	{
		free(dir_operand);
		free(curpath);
		return (1);
	}
	ft_dprintf(2, "canonical   = %s\n", curpath);
	return (0);
}
