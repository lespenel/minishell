/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 11:13:28 by ccouble           #+#    #+#             */
/*   Updated: 2024/01/10 05:24:47 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_string.h"
#include "ft_mem.h"
#include "ft_util.h"

static char	*search_envpath(char *file, char *space, char *envpath);

char	*ft_get_path(char *file, char *envp[])
{
	char		*envpath;
	char *const	space = ft_strchr(file, ' ');

	if (space && ft_memchr(file, '/', space - file))
		return (ft_strndup(file, space - file));
	if (space == NULL && ft_strchr(file, '/'))
		return (ft_strdup(file));
	envpath = ft_getenv(envp, "PATH");
	if (envpath == NULL)
		return (NULL);
	envpath = ft_strdup(envpath);
	if (envpath == NULL)
		return (NULL);
	return (search_envpath(file, space, envpath));
}

static char	*search_envpath(char *file, char *space, char *envpath)
{
	char	*path;

	path = ft_strtok(envpath, ":");
	while (path)
	{
		if (space)
			*space = '\0';
		path = ft_strjoin_three(path, "/", file);
		if (space)
			*space = ' ';
		if (path == NULL)
		{
			free(envpath);
			return (NULL);
		}
		if (access(path, F_OK) == 0)
		{
			free(envpath);
			return (path);
		}
		free(path);
		path = ft_strtok(NULL, ":");
	}
	free(envpath);
	return (NULL);
}
