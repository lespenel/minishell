/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:19:23 by ccouble           #+#    #+#             */
/*   Updated: 2024/02/27 02:56:38 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"

int	ft_add_vector(t_vector *this, const void *data, size_t count)
{
	size_t	currentelem;

	if (count == 0)
		return (-1);
	while (this->size + count >= this->allocated)
	{
		ft_set_alloc_size(this, count);
		if (ft_reallocate_vector(this))
			return (-1);
	}
	currentelem = this->size * this->elemsize;
	ft_memcpy(this->array + currentelem, data, this->elemsize * count);
	this->size += count;
	return (0);
}
