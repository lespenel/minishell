/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:17:00 by ccouble           #+#    #+#             */
/*   Updated: 2023/12/26 02:31:31 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_mem.h"

void	ft_remove_vector(t_vector *this, size_t i)
{
	const size_t	rmi = i * this->elemsize;
	const size_t	sizei = (this->size - 1) * this->elemsize;
	void			*rmptr;

	rmptr = this->array + rmi;
	ft_memmove(rmptr, rmptr + this->elemsize, sizei - rmi);
	this->size--;
}
