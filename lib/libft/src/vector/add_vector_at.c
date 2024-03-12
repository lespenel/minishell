/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vector_at.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 01:47:35 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/12 02:10:37 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "ft_mem.h"

int	add_vector_at(t_vector *this, const void *new, size_t at)
{
	size_t	i;

	i = 0;
	if (at > this->size)
		return (-1);
	if (this->size + 1 >= this->allocated)
	{
		set_alloc_size(this, 1);
		if (reallocate_vector(this))
			return (-1);
	}
	while (i < (this->size - at))
	{
		ft_memcpy(this->array + (this->size - i) * this->elemsize, this->array
			+ (this->size - i - 1) * this->elemsize, this->elemsize);
		++i;
	}
	ft_memcpy(this->array + (at * this->elemsize), new, this->elemsize);
	this->size += 1;
	return (0);
}
