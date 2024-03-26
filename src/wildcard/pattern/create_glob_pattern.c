/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_glob_pattern.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 02:45:28 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/26 07:20:03 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "util.h"
#include "wildcard.h"
#include <stdlib.h>

int	create_glob_pattern(t_wild *wild)
{
	char		*entry;
	t_pattern	pattern;

	if (wild->globignore == NULL)
		return (0);
	entry = ft_strdup(wild->globignore);
	if (entry == NULL)
		return (-1);
	entry = ft_strtok(entry, ":");
	while (entry)
	{
		if (ms_strchr(entry, '/'))
			pattern.type = FILENAME;
		else
			pattern.type = NO_STAR;
		if (fill_pattern(&pattern.pattern, entry) == -1
			|| add_vector(&wild->glob_patterns, &pattern, 1) == -1)
		{
			free(entry);
			return (-1);
		}
		entry = ft_strtok(NULL, ":");
	}
	free(entry);
	return (0);
}
