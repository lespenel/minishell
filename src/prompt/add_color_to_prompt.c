/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_color_to_prompt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:14:26 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/10 07:15:54 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "vector.h"

int	add_color_to_prompt(t_vector *prompt, char *color)
{
	if (add_vector(prompt, "\001", 1) == -1)
		return (-1);
	if (add_vector(prompt, color, ft_strlen(color)) == -1)
		return (-1);
	if (add_vector(prompt, "\002", 1) == -1)
		return (-1);
	return (0);
}
