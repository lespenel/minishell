/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_backslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 00:29:58 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/07 06:53:14 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "vector.h"
#include "ft_string.h"
#include <stdlib.h>

static int	add_match_tok(t_vector *new_flst, char **s);

int	add_backslash(t_vector *filenames)
{
	size_t		i;
	t_vector	new_flst;

	i = 0;
	init_vector(&new_flst, sizeof(char *));
	while (i < filenames->size)
	{
		if (add_match_tok(&new_flst, at_vector(filenames, i)) == -1)
		{
			clear_string_vector(&new_flst);
			return (-1);
		}
		++i;
	}
	clear_string_vector(filenames);
	*filenames = new_flst;
	return (0);
}

static int	add_match_tok(t_vector *new_flst, char **s)
{
	char		*token;
	size_t		i;
	size_t		j;

	token = malloc(sizeof(char) * (ft_strlen(*s) * 2) + 1);
	if (token == NULL)
		return (-1);
	i = 0;
	j = 0;
	while (s[0][i])
	{
		token[i + j] = '\\';
		++j;
		token[i + j] = s[0][i];
		++i;
	}
	token[i + j] = '\0';
	if (add_vector(new_flst, &token, 1) == -1)
		return (-1);
	return (0);
}
