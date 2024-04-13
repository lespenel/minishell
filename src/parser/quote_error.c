/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 03:23:03 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/13 03:23:23 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	quote_error(char *s)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (is_quote(*s))
		{
			ret = to_next_quote(s);
			if (ret == 0)
				return (1);
			s += ret;
		}
		else
			++s;
	}
	return (0);
}
