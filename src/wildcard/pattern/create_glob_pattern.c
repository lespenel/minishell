/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_glob_pattern.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 02:45:28 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/26 05:01:58 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "util.h"
#include "vector.h"
#include "wildcard.h"
#include <stdio.h>
#include <stdlib.h>

int	create_glob_pattern(t_wildcard *wild)
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
		print_lexer(&pattern.pattern);
		printf("entry = %s\n", entry);
		entry = ft_strtok(NULL, ":");
	}
	free(entry);
	return (0);
}
