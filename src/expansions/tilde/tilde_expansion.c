/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:44:01 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/07 04:17:32 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "lexer.h"
#include "minishell.h"
#include "vector.h"
#include "ft_string.h"
#include <stdlib.h>
#include <unistd.h>

static int	tilde_on_word(t_ms *ms, char **s);
static int	replace_tilde(t_ms *ms, char **s, size_t i);

int	tilde_expansion(t_ms *ms, t_lexer_tok *token)
{
	size_t			i;
	t_redirection	*redirection;

	i = 0;
	while (i < token->args.size)
	{
		if (tilde_on_word(ms, at_vector(&token->args, i)) == -1)
			return (-1);
		++i;
	}
	i = 0;
	while (i < token->redirections.size)
	{
		redirection = at_vector(&token->redirections, i);
		if (redirection->type != HERE_DOC)
		{
			if (tilde_on_word(ms, &redirection->file) == -1)
				return (-1);
		}
		++i;
	}
	return (0);
}

static int	tilde_on_word(t_ms *ms, char **s)
{
	size_t	i;

	i = 0;
	while ((*s)[i] && (*s)[i] != '/')
		++i;
	if (i == 2 && (*s)[1] != '+')
		return (0);
	if ((*s[0]) == '~' && (i == 1 || i == 2))
		return (replace_tilde(ms, s, i));
	return (0);
}

static int	replace_tilde(t_ms *ms, char **s, size_t i)
{
	t_vector	new;
	char		*var;

	init_vector(&new, sizeof(char));
	if (i == 1)
		var = "HOME";
	else
		var = "PWD";
	var = ms_getenv(&ms->env, var);
	if (var)
	{
		if (add_vector(&new, var, ft_strlen(var)) == -1)
		{
			clear_vector(&new);
			return (-1);
		}
		if (add_vector(&new, *s + i, ft_strlen(*s + i)) == -1)
		{
			clear_vector(&new);
			return (-1);
		}
		free(*s);
		*s = new.array;
	}
	return (0);
}
