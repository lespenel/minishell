/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:24:54 by ccouble           #+#    #+#             */
/*   Updated: 2023/12/22 14:42:28 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include <stdlib.h>

void	ft_clear_vector(t_vector *this)
{
	if (this->array)
		free(this->array);
	this->array = NULL;
	this->allocated = 0;
	this->size = 0;
}
