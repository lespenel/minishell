/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:25:37 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 10:26:31 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "lexer.h"

char	*ms_strchr(char *str, char c)
{
	size_t	i;

	i = 0;
	i = next_char(str, -1);
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		if (is_quote(str[i]))
		{
			i += to_next_quote(str + i);
		}
		i = next_char(str, i);
	}
	return (NULL);
}
