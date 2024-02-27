/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reallocate_vector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 07:30:36 by ccouble           #+#    #+#             */
/*   Updated: 2024/02/27 02:56:54 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"
#include <stdlib.h>

int	ft_reallocate_vector(t_vector *this)
{
	size_t	elem;
	void	*ptr;

	elem = this->size * this->elemsize;
	ptr = malloc(this->allocated * this->elemsize);
	if (ptr == NULL)
	{
		if (this->array)
			free(this->array);
		this->array = NULL;
		return (-1);
	}
	ft_memcpy(ptr, this->array, elem);
	ft_memset(ptr + elem, 0, (this->allocated * this->elemsize) - elem);
	if (this->array)
		free(this->array);
	this->array = ptr;
	return (0);
}
