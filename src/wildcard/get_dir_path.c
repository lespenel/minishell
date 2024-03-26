/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 05:22:00 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/26 07:15:58 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "wildcard.h"
#include <dirent.h>

DIR	*get_dir_path(t_wild *wild, char *path)
{
	char	*wd;
	DIR		*dir;

	wd = ft_strdup(wild->wd);
	if (wd == NULL)
		return (NULL);
	if (path)
	{
		if (wild->wd[wild->wd_size -1] == '/')
			wd = ft_strjoin_fs1(wd, path);
		else
		{
			wd = ft_strjoin_fs1(wd, "/");
			if (wd == NULL)
				return (NULL);
			wd = ft_strjoin_fs1(wd, path);
		}
		if (wd == NULL)
			return (NULL);
	}
	dir = opendir(wd);
	return (dir);
}
