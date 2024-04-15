/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_filenames.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:41:39 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/15 05:36:54 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "vector.h"
#include "wildcard.h"
#include "ft_string.h"
#include <signal.h>

static size_t	array_partition(t_vector *fnames, ssize_t start, ssize_t end);
static void		swap_str(char **s1, char **s2);

void	sort_filenames(t_vector *filenames, ssize_t start, ssize_t end)
{
	ssize_t	pivot_index;

	if (start < end && g_sig != SIGINT)
	{
		pivot_index = array_partition(filenames, start, end);
		sort_filenames(filenames, start, pivot_index - 1);
		sort_filenames(filenames, pivot_index + 1, end);
	}
}

static size_t	array_partition(t_vector *filenames, ssize_t start, ssize_t end)
{
	char		*pivot;
	ssize_t		i;
	ssize_t		j;
	char		**s;

	i = start;
	j = start;
	s = at_vector(filenames, end);
	pivot = *s;
	while (i < end)
	{
		s = at_vector(filenames, i);
		if (ms_strcmp(*s, pivot) <= 0)
		{
			swap_str(at_vector(filenames, j), s);
			++j;
		}
		++i;
	}
	swap_str(at_vector(filenames, j), at_vector(filenames, end));
	return (j);
}

static	void	swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}
