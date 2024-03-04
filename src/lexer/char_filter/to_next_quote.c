/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_next_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:15:17 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/04 13:16:42 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

int	to_next_quote(char *s)
{
	ssize_t	i;
	char	c;

	i = 0;
	c = '\'';
	if (s[i] == '\'' || s[i] == '\"')
		c = s[i];
	if (s[i] == c)
	{
		while (s[i])
		{
			i++;
			if (s[i] == c)
				return (i);
		}
	}
	return (0);
}
