/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_aliases.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 23:20:31 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 02:12:52 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chargroups.h"
#include "env.h"
#include "ft_string.h"
#include "minishell.h"
#include "lexer.h"
#include "vector.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

static int	alias_already_used(t_vector *used, char *alias);
static int	do_alias(t_lexer_tok *tok, t_vector *used, char *arg, char *alias);
static int	add_alias(t_lexer_tok *token, char *alias);
static int	dup_and_add(t_vector *used, char *str);

int	expand_aliases(t_ms *ms, t_lexer_tok *token)
{
	char		**arg;
	char		*alias;
	t_vector	used;

	if (token->args.size == 0)
		return (0);
	init_vector(&used, sizeof(char *));
	arg = at_vector(&token->args, 0);
	alias = ms_getenv(&ms->aliases, *arg);
	while (alias)
	{
		if (do_alias(token, &used, *arg, alias) == -1)
		{
			clear_string_vector(&used);
			return (-1);
		}
		if (token->args.size == 0)
			break ;
		arg = at_vector(&token->args, 0);
		alias = ms_getenv(&ms->aliases, *arg);
		if (alias_already_used(&used, *arg))
			alias = NULL;
	}
	clear_string_vector(&used);
	return (0);
}

static int	alias_already_used(t_vector *used, char *alias)
{
	size_t	i;
	char	**arg;

	i = 0;
	while (i < used->size)
	{
		arg = at_vector(used, i);
		if (ft_strcmp(alias, *arg) == 0)
			return (1);
		++i;
	}
	return (0);
}

static int	do_alias(t_lexer_tok *tok, t_vector *used, char *arg, char *alias)
{
	if (dup_and_add(used, arg) == -1)
		return (-1);
	if (add_alias(tok, alias) == -1)
		return (-1);
	return (0);
}

static int	add_alias(t_lexer_tok *token, char *alias)
{
	t_vector	split;
	char		**arg;

	init_vector(&split, sizeof(char *));
	if (ft_split_vector(&split, alias, DEFAULT_IFS) == -1)
	{
		clear_string_vector(&split);
		return (-1);
	}
	arg = at_vector(&token->args, 0);
	free(*arg);
	remove_vector(&token->args, 0);
	if (merge_vector(&token->args, &split, 0) == -1)
	{
		clear_string_vector(&split);
		return (-1);
	}
	clear_vector(&split);
	return (0);
}

static int	dup_and_add(t_vector *used, char *str)
{
	char	*new;

	new = ft_strdup(str);
	if (new == NULL)
		return (-1);
	if (add_vector(used, &new, 1) == -1)
	{
		free(new);
		return (-1);
	}
	return (0);
}
