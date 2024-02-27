/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_alloc_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:01:45 by ccouble           #+#    #+#             */
/*   Updated: 2024/01/07 08:56:15 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void	ft_set_alloc_size(t_vector *this, size_t count)
{
	if (this->size + count >= this->allocated)
	{
		if (this->allocated == 0)
			this->allocated = BASE_ALLOC;
		else
			this->allocated *= 2;
		return ;
	}
}
