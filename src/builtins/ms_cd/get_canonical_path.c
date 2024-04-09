/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_canonical_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:25:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 06:52:29 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "util.h"
#include "vector.h"
#include "builtins.h"
#include <stdlib.h>

static	int		remove_dots(t_vector *split_path);
static	void	remove_last_slash(t_vector *n_path);

int		get_canonical_path(t_env *env, char **curpath, char *dir_operand)
{
	t_vector	new;
	t_vector	split;

	init_vector(&new, sizeof(char));
	init_vector(&split, sizeof(char *));
	if (add_vector(&new, "/", 1) == -1
		|| ft_split_vector(&split, *curpath, '/') == -1
		|| remove_dots(&split) == -1
		|| remove_dot_dot(env, &new, &split, dir_operand) == -1)
	{
		clear_vector(&split);
		clear_vector(&new);
		return (-1);
	}
	remove_last_slash(&new);
	clear_vector(&split);
	free(*curpath);
	*curpath = ft_strdup(new.array);
	clear_vector(&new);
	if (*curpath == NULL)
		return (-1);
	return (0);
}

static	void	remove_last_slash(t_vector *n_path)
{
	char	*curr;

	curr = at_vector(n_path, n_path->size - 1);
	if (n_path->size > 1 && *curr == '/')
		remove_vector(n_path, n_path->size - 1);
}

static	int	remove_dots(t_vector *split_path)
{
	char	**curr;
	size_t	i;

	i = 0;
	while (i < split_path->size)
	{
		curr = at_vector(split_path, i);
		if (ft_strcmp(*curr, ".") == 0)
		{
			free(*curr);
			remove_vector(split_path, i);
		}
		else
			++i;
	}
	return (0);
}
