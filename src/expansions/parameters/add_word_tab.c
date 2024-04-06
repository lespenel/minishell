/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 06:41:47 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/06 06:41:55 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

int	add_word_tab(t_vector *tab, t_vector *word)
{
	if (add_vector(tab, &word->array, 1) == -1)
		return (-1);
	init_vector(word, sizeof(char));
	return (0);
}
