/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_identifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 07:50:13 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/16 11:45:15 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_char.h"

int	is_valid_identifier(char *str)
{
	if (*str == '\0')
		return (0);
	if (*str >= '0' && *str <= '9')
		return (0);
	while (*str)
	{
		if (ft_isalnum(*str) == 0 && *str != '=' && *str != '_')
			return (0);
		++str;
	}
	return (1);
}
