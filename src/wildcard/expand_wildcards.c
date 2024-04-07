/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/07 08:53:25 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "vector.h"
#include "wildcard.h"
#include <stdlib.h>

static int		expand_redirect(t_env *env, t_lexer_tok *token);
static int		expand_comand(t_env *env, t_lexer_tok *token);
static ssize_t	add_filename_lexer(t_vector *lst, t_vector *fnames, ssize_t i);

int	expand_wildcards(t_env *env, t_lexer_tok *token)
{
	if (expand_redirect(env, token) == -1
		|| expand_comand(env, token) == -1)
		return (-1);
	return (0);
}

static int	expand_comand(t_env *env, t_lexer_tok *token)
{
	size_t		i;
	ssize_t		ret;
	char		**s;
	t_vector	file_names;

	i = 0;
	while (i < token->args.size)
	{
		init_vector(&file_names, sizeof (char *));
		s = at_vector(&token->args, i);
		if (ms_strchr(*s, '*'))
		{
			if (wildcard_handling(env, &file_names, *s) == -1)
			{
				clear_string_vector(&file_names);
				return (-1);
			}
			ret = add_filename_lexer(&token->args, &file_names, i);
			if (ret == -1)
				return (-1);
			i += ret;
		}
		++i;
	}
	return (0);
}

static int	expand_redirect(t_env *env, t_lexer_tok *token)
{
	t_redirection	*redir;
	size_t			i;

	i = 0;
	while (i < token->redirections.size)
	{
		redir = at_vector(&token->redirections, i);
		if (redir->type != HERE_DOC)
		{
			init_vector(&redir->newtab, sizeof(char *));
			if (ms_strchr(redir->file, '*'))
			{
				if (wildcard_handling(env, &redir->newtab, redir->file) == -1)
				{
					clear_string_vector(&redir->newtab);
					return (-1);
				}
			}
		}
		++i;
	}
	return (0);
}

static ssize_t	add_filename_lexer(t_vector *lst, t_vector *fnames, ssize_t i)
{
	char	**s;

	if (fnames->size > 0)
	{
		s = at_vector(lst, i);
		free(*s);
		remove_vector(lst, i);
		if (merge_vector(lst, fnames, i) == -1)
		{
			clear_string_vector(fnames);
			return (-1);
		}
		i += fnames->size - 1;
		clear_vector(fnames);
	}
	return (i);
}
