/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_filter_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 02:34:21 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/01 06:18:28 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_word(char c)
{
	if (is_operand(c) == 0 && is_blank(c) == 0 && is_quote(c) == 0)
		return (1);
	return (0);
}

int	is_operand(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == ',' || c == '('
		|| c == ')' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	to_next_quote(char *s)
{
	size_t	j;
	char	c;

	j = 0;
	c = '\'';
	if (s[j] == '\'' || s[j] == '\"')
		c = s[j];
	if (s[j] == c)
	{
		while (s[j])
		{
			j++;
			if (s[j] == c)
				return (j);
		}
	}
	return (0);
}
