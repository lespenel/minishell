/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 06:36:16 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/25 06:39:59 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include "ft_string.h"

static char	*search_envpath(char *file, char *envpath);

char	*get_path(t_ms *ms, char *name)
{
	char		*envpath;

	if (*name == '\0' || *name == ' ')
		return (NULL);
	envpath = ms_getenv(&ms->env, "PATH");
	if (envpath == NULL)
		return (NULL);
	envpath = ft_strdup(envpath);
	if (envpath == NULL)
		return (NULL);
	return (search_envpath(name, envpath));
}


static char	*search_envpath(char *file, char *envpath)
{
	char	*path;

	path = ft_strtok(envpath, ":");
	while (path)
	{
		path = ft_strjoin_three(path, "/", file);
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
