/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_value_vector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 07:28:41 by ccouble           #+#    #+#             */
/*   Updated: 2024/02/27 02:57:59 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

int	ft_set_value_vector(t_vector *this, const void *data, size_t i)
{
	size_t	j;
	size_t	currentelem;

	if (i >= this->allocated)
	{
		while (i >= this->allocated)
		{
			if (this->allocated == 0)
				this->allocated = BASE_ALLOC;
			else
				this->allocated *= 2;
		}
		if (ft_reallocate_vector(this))
			return (-1);
	}
	j = 0;
	currentelem = i * this->elemsize;
	while (j < this->elemsize)
	{
		((char *)this->array)[(currentelem) + j] = ((char *)data)[j];
		++j;
	}
	if (i > this->size)
		this->size = i;
	return (0);
}
