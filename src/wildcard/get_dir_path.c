/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 05:22:00 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/28 09:31:04 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "wildcard.h"
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

DIR	*get_dir_path(t_wild *wild, char *path)
{
	char	*wd;
	char	*tmp;
	DIR		*dir;

	wd = ft_strdup(wild->wd);
	if (wd == NULL)
		return (NULL);
	if (path)
	{
		tmp = ft_strjoin(wd, path);
		free(wd);
		if (tmp == NULL)
			return (NULL);
		wd = tmp;
	}
	dir = opendir(wd);
	if (dir == NULL)
		errno = 0;
	free(wd);
	return (dir);
}
