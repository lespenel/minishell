/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_match_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:18:52 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 14:21:03 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include <stdlib.h>

int	add_match_tok(t_lexer *matches, char *s)
{
	t_lexer_tok	token;
	size_t		i;
	size_t		j;

	token.content = malloc(sizeof(char) * (ft_strlen(s) * 2) + 1);
	if (token.content == NULL)
		return (-1);
	i = 0;
	j = 0;
	while (s[i])
	{
		token.content[i + j] = '\\';
		++j;
		token.content[i + j] = s[i];
		++i;
	}
	token.content[i + j] = '\0';
	token.type = WORD;
	if (add_vector(matches, &token, 1) == -1)
		return (-1);
	return (0);
}
