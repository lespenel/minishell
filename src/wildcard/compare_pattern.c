/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:19:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/25 05:37:52 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	compare_pattern(t_wildcard *wildcard, t_lexer *filenames)
{
	if (get_matching_dirname(wildcard, filenames, 0) == -1)
		return (-1);
	if (wildcard->nb_dir == (int)wildcard->patterns.size)
		return (0);
	if (get_matching_filenames(wildcard, filenames) == -1)
		return (-1);
	return (0);
}
