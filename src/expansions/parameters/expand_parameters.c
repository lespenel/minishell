/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:01:01 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/07 05:10:42 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "vector.h"
#include "expander.h"

static int	expand_redirections(t_ms *ms, t_lexer_tok *token);
static int	expand_word(t_ms *ms, char *s, t_vector *new);

int	expand_parameters(t_ms *ms, t_lexer_tok *token)
{
	size_t			i;
	t_vector		newtab;
	char			**s;

	i = 0;
	while (i < token->args.size)
	{
		init_vector(&newtab, sizeof(char *));
		s = at_vector(&token->args, i);
		if (expand_word(ms, *s, &newtab) == -1)
		{
			clear_vector(&newtab);
			return (-1);
		}
		free(*s);
		remove_vector(&token->args, i);
		if (merge_vector(&token->args, &newtab, i) == -1)
		{
			clear_vector(&newtab);
			return (-1);
		}
		i += newtab.size;
		clear_vector(&newtab);
	}
	return (expand_redirections(ms, token));
}

static int	expand_redirections(t_ms *ms, t_lexer_tok *token)
{
	t_redirection	*redirection;
	size_t			i;

	i = 0;
	while (i < token->redirections.size)
	{
		redirection = at_vector(&token->redirections, i);
		if (redirection->type != HERE_DOC)
		{
			if (expand_word(ms, redirection->file, &redirection->newtab) == -1)
				return (-1);
		}
		++i;
	}
	return (0);
}

static int	expand_word(t_ms *ms, char *s, t_vector *new)
{
	ssize_t		wlen;
	size_t		i;
	t_vector	newstring;

	init_vector(&newstring, sizeof(char));
	i = 0;
	while (s[i])
	{
		wlen = expand_substr(ms, &newstring, s + i, new);
		if (wlen == -1)
		{
			clear_vector(&newstring);
			return (-1);
		}
		i += wlen;
	}
	if (newstring.size != 0)
	{
		if (add_vector(new, &newstring.array, 1) == -1)
		{
			clear_vector(&newstring);
			return (-1);
		}
	}
	return (0);
}
