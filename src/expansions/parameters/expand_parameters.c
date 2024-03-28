/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:01:01 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/28 04:19:13 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_string.h"
#include "minishell.h"
#include "vector.h"
#include "expander.h"

static int	expand_word(t_ms *ms, char **s);

int	expand_parameters(t_ms *ms, t_lexer_tok *token)
{
	size_t			i;
	t_redirection	*redirection;

	i = 0;
	while (i < token->args.size)
	{
		if (expand_word(ms, at_vector(&token->args, i)) == -1)
			return (-1);
		++i;
	}
	i = 0;
	while (i < token->redirections.size)
	{
		redirection = at_vector(&token->redirections, i);
		if (expand_word(ms, &redirection->file) == -1)
			return (-1);
		++i;
	}
	return (0);
}

static int	expand_word(t_ms *ms, char **s)
{
	ssize_t		wlen;
	size_t		i;
	t_vector	newstring;

	init_vector(&newstring, sizeof(char));
	i = 0;
	while ((*s)[i])
	{
		wlen = expand_substr(ms, &newstring, *s + i);
		if (wlen == -1)
		{
			clear_vector(&newstring);
			return (-1);
		}
		i += wlen;
	}
	free(*s);
	*s = newstring.array;
	return (0);
}
