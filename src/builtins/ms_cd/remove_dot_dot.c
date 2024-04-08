/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dot_dot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 01:48:30 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/08 01:53:44 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "vector.h"
#include <stdlib.h>
#include <sys/stat.h>

static	void	remove_before_dir(t_vector *n_path);
static	int		is_directory(char *path);

int		remove_dot_dot(t_vector *new_path, t_vector *split_path)
{
	char	**curr;
	size_t	i;

	i = 0;
	while (i < split_path->size)
	{
		curr = at_vector(split_path, i);
		if (ft_strcmp(*curr, ".."))
		{
			if (add_vector(new_path, *curr, ft_strlen(*curr)) == -1
				|| add_vector(new_path, "/", 1) == -1)
				return (-1);
			if (is_directory(new_path->array) == 0)
				return (0);
			++i;
		}
		else 
		{
			free(*curr);
			remove_vector(split_path, i);
			remove_before_dir(new_path);
		}
	}
	return (0);
}

static	void	remove_before_dir(t_vector *n_path)
{
	size_t	i;
	char	*curr;
	size_t	n_len;

	i = 0;
	n_len = 1;
	if (n_path->size == 1)
		return ;
	curr = at_vector(n_path, n_path->size - 1 - n_len);
	while (*curr != '/')
	{
		++n_len;
		curr = at_vector(n_path, n_path->size - 1 - n_len);
	}
	while (i < n_len)
	{
		remove_vector(n_path, n_path->size - 1);
		++i;
	}
}

static	int	is_directory(char *path)
{
	struct stat buff;
	int	ret;

	if (stat(path, &buff) < 0)
		ret = 0;
	else
		ret = S_ISDIR(buff.st_mode);
	return (ret);
}
