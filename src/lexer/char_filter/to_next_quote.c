/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_next_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:15:17 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/20 02:47:46 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <util.h>

int	to_next_quote(char *s)
{
	ssize_t	i;
	char	c;

	i = 0;
	c = s[i];
	while (s[i])
	{
		++i;
		if (s[i] == c)
			return (i);
	}
	return (0);
}
