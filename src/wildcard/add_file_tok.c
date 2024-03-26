/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 05:56:56 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/26 05:58:02 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "wildcard.h"
#include <stdlib.h>

int	add_file_tok(t_lexer *filenames, char *s)
{
	t_lexer_tok	token;

	token.content = ft_strdup(s);
	if (token.content == NULL)
		return (-1);
	token.type = WORD;
	if (add_vector(filenames, &token, 1) == -1)
	{
		free(token.content);
		return (-1);
	}
	return (0);
}
