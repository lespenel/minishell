/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:13:30 by ccouble           #+#    #+#             */
/*   Updated: 2024/01/14 22:48:45 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <stddef.h>

# define BASE_ALLOC 16

typedef struct s_vector
{
	size_t	elemsize;
	size_t	size;
	size_t	allocated;
	void	*array;

}	t_vector;

int		ft_add_vector(t_vector *this, const void *data, size_t count);
void	*ft_get_vector(t_vector *this, size_t i);
int		ft_set_value_vector(t_vector *this, const void *data, size_t i);
int		ft_reallocate_vector(t_vector *this);
void	ft_clear_vector(t_vector *this);
void	ft_remove_vector(t_vector *this, size_t i);
void	ft_init_vector(t_vector *this, size_t elemsize);
void	ft_set_alloc_size(t_vector *this, size_t count);

#endif
