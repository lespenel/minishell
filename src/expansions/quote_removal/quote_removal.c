/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:57:23 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/12 10:24:59 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include <stdio.h>
#include "expander.h"
#include <stdlib.h>
#include <unistd.h>

int	quote_removal(t_lexer_tok *token)
{
	size_t			i;
	char			**s;
	t_redirection	*redirection;

	i = 0;
	while (i < token->args.size)
	{
		s = at_vector(&token->args, i);
		if (remove_quotes(s) == -1)
			return (-1);
		if (*s == NULL)
			remove_vector(&token->args, i);
		else
			++i;
	}
	i = 0;
	while (i < token->redirections.size)
	{
		redirection = at_vector(&token->redirections, i);
		if (remove_quotes(&redirection->file) == -1)
			return (-1);
		++i;
	}
	return (0);
}
