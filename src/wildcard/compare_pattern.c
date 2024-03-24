/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:19:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 13:53:53 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "wildcard.h"

int	get_matching_filenames(t_pattern *pattern, t_lexer *filenames);

int	compare_pattern(t_wildcard *wildcard, t_lexer *filenames)
{
	t_pattern	*pattern;
	int			i;

	i = 0;
	if (get_matching_dirname(wildcard, filenames, 0) == -1)
		return (-1);
	pattern = at_vector(&wildcard->patterns, wildcard->nb_dir);
	/*
	if (wildcard->nb_dir < (int)wildcard->patterns.size)
	{
		if (get_matching_filenames(pattern, filenames) == -1)
			return (-1);
	}*/
	(void)i;
	(void)pattern;
	return (0);
}

int	get_matching_filenames(t_pattern *pattern, t_lexer *filenames)
{
	(void)pattern;
	(void)filenames;
	return (0);
}
