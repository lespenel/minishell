/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:25:37 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/06 23:01:35 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "lexer.h"

char	*ms_strchr(char *str, char c)
{
	size_t	i;

	i = 0;
	if (str == NULL || *str == '\0')
		return (NULL);
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
