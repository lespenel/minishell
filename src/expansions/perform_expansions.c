/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 01:41:37 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 06:24:33 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lexer.h"
#include "minishell.h"
#include "signals.h"
#include "vector.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static int	check_redirections_param(t_lexer_tok *token);
static int	check_redirections_wildcard(t_lexer_tok *token);

int	perform_expansions(t_ms *ms, t_lexer_tok *token)
{
	if (tilde_expansion(ms, token) == -1)
		return (-1);
	if (expand_aliases(ms, token) == -1)
		return (-1);
	if (expand_parameters(ms, token) == -1)
		return (-1);
	if (check_redirections_param(token) == -1)
		return (1);
	if (expand_wildcards(&ms->env, token) == -1)
		return (-1);
	if (g_sig == SIGINT)
		return (0);
	if (check_redirections_wildcard(token) == -1)
		return (1);
	if (quote_removal(token) == -1)
		return (-1);
	return (0);
}

static int	check_redirections_param(t_lexer_tok *token)
{
	size_t			i;
	t_redirection	*redirection;
	char			**s;

	i = 0;
	while (i < token->redirections.size)
	{
		redirection = at_vector(&token->redirections, i);
		if (redirection->type != HERE_DOC && redirection->newtab.size == 1)
		{
			redirection = at_vector(&token->redirections, i);
			free(redirection->file);
			s = at_vector(&redirection->newtab, 0);
			redirection->file = *s;
			clear_vector(&redirection->newtab);
		}
		else if (redirection->type != HERE_DOC)
		{
			dprintf(2, "%s: ambiguous redirect\n", redirection->file);
			return (-1);
		}
		++i;
	}
	return (0);
}

static int	check_redirections_wildcard(t_lexer_tok *token)
{
	size_t			i;
	t_redirection	*redirection;
	char			**s;

	i = 0;
	while (i < token->redirections.size)
	{
		redirection = at_vector(&token->redirections, i);
		if (redirection->type != HERE_DOC && redirection->newtab.size == 1)
		{
			redirection = at_vector(&token->redirections, i);
			free(redirection->file);
			s = at_vector(&redirection->newtab, 0);
			redirection->file = *s;
			clear_vector(&redirection->newtab);
		}
		else if (redirection->type != HERE_DOC && redirection->newtab.size != 0)
		{
			dprintf(2, "%s: ambiguous redirect\n", redirection->file);
			return (-1);
		}
		++i;
	}
	return (0);
}
