/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:51:24 by ccouble           #+#    #+#             */
/*   Updated: 2023/11/30 09:51:37 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void	ft_init_vector(t_vector *this, size_t elemsize)
{
	this->elemsize = elemsize;
	this->allocated = 0;
	this->size = 0;
	this->array = NULL;
}
