/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:59:18 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/18 06:23:46 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include <stdio.h>
#include <unistd.h>

int	ms_cd(t_env	*env, char **args)
{
	const int	argc = get_argc(args);
	char		*path;

	if (argc > 2)
	{
		dprintf(2, "cd: too many arguments");
		return (1);
	}
	path = ms_getenv(env, "PWD");
	if (path == NULL)
		return (-1);
	path = ft_strjoin_three(path, "/", args[argc - 1]);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (-1);
	}
	if (ms_setenv(env, "PWD", path) == -1)
		return (-1);
	return (0);
}
