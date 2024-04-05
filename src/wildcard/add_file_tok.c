/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 05:56:56 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/05 01:33:44 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "wildcard.h"
#include <stdlib.h>

int	add_file_tok(t_vector *filenames, char *s)
{
	char	*token;

	token = ft_strdup(s);
	if (token == NULL)
		return (-1);
	if (add_vector(filenames, &token, 1) == -1)
	{
		free(token);
		return (-1);
	}
	return (0);
}
