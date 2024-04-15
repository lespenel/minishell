/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_pattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 04:15:58 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/15 04:17:12 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "wildcard.h"

int	check_end_pattern(char *to_find, char *f_name)
{
	ssize_t			i;
	const ssize_t	file_l = ft_strlen(f_name);
	const ssize_t	find_l = ft_strlen(to_find);

	i = 0;
	if (file_l < find_l)
		return (0);
	while (i != find_l && f_name[file_l - i - 1] == to_find[find_l - i - 1])
		++i;
	return (i == find_l);
}
