/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 01:41:37 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/04 16:00:19 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lexer.h"
#include "minishell.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

static int	check_redirections(t_lexer_tok *token);

int	perform_expansions(t_ms *ms, t_lexer_tok *token)
{
	if (tilde_expansion(ms, token) == -1)
		return (-1);
	if (expand_parameters(ms, token) == -1)
		return (-1);
	if (word_split(ms, token) == -1)
		return (-1);
	if (check_redirections(token) == -1)
		return (-1);
	if (quote_removal(token) == -1)
		return (-1);
	return (0);
}

static int	check_redirections(t_lexer_tok *token)
{
	size_t			i;
	t_redirection	*redirection;
	char			**s;

	i = 0;
	while (i < token->redirections.size)
	{
		redirection = at_vector(&token->redirections, i);
		if (redirection->newtab.size == 1)
		{
			redirection = at_vector(&token->redirections, i);
			free(redirection->file);
			s = at_vector(&redirection->newtab, 0);
			redirection->file = *s;
			clear_vector(&redirection->newtab);
		}
		else
		{
			// What I did is bad here
			dprintf(2, "%s: ambiguous redirect\n", redirection->file);
			return (-1);
		}
		++i;
	}
	return (0);
}
