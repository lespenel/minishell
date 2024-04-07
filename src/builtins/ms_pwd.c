/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:50:20 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/07 22:35:57 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "env.h"
#include "builtins.h"
#include "ft_string.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int	ms_pwd(t_env *env, char **args)
{
	char	*wd;

	(void)args;
	wd = ms_getenv(env, "PWD");
	if (wd != NULL)
	{
		if (ft_dprintf(1, "%s\n", wd) == -1)
			return (1);
		return (0);
	}
	wd = getcwd(NULL, 0);
	if (wd == NULL)
	{
		ft_dprintf(2, "minishell: pwd: %s\n", strerror(errno));
		return (1);
	}
	if (ft_dprintf(1, "%s\n", wd) == -1)
	{
		free(wd);
		return (1);
	}
	free(wd);
	return (0);
}
