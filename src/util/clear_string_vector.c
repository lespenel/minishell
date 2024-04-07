/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_string_vector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 06:44:18 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/07 08:18:29 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdlib.h>

void	clear_string_vector(t_vector *this)
{
	char	**curr;
	size_t	i;

	i = 0;
	while (i < this->size)
	{
		curr = at_vector(this, i);
		free(*curr);
		++i;
	}
	clear_vector(this);
}
