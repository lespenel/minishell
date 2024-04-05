/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:30:17 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/05 18:34:34 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include "ft_string.h"
#include <stdio.h>
#include <stdlib.h>
#include "ft_string.h"
#include "lexer.h"
#include "minishell.h"
#include "vector.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

static int	fill_newtab(t_ms *ms, t_vector *newtab, char *s);
static char	**ft_split(const char *s, char *delim);

int	word_split(t_ms *ms, t_lexer_tok *token)
{
	size_t		i;
	char		**s;
	t_vector	newtab;
	t_redirection	*redirection;

	i = 0;
	while (i < token->args.size)
	{
		s = at_vector(&token->args, i);
		init_vector(&newtab, sizeof(char *));
		if (fill_newtab(ms, &newtab, *s) == -1)
			return (-1);
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
	i = 0;
	while (i < token->redirections.size)
	{
		redirection = at_vector(&token->redirections, i);
		init_vector(&redirection->newtab, sizeof(char *));
		if (fill_newtab(ms, &redirection->newtab, redirection->file) == -1)
			return (-1);
		++i;
	}
	return (0);
}

static int	fill_newtab(t_ms *ms, t_vector *newtab, char *s)
{
	char	**strs;
	size_t	i;

	strs = ft_split(s, get_ifs(&ms->env));
	if (strs == NULL)
		return (-1);
	i = 0;
	while (strs[i])
		++i;
	newtab->array = strs;
	newtab->allocated = i;
	newtab->size = i;
	return (0);
}

static char	**ft_split(const char *s, char *delim)
{
	size_t	count;
	char	**strs;
	size_t	i;
	size_t	j;

	while (*s && ft_strchr(delim, *s))
		++s;
	count = ft_count_words(s, delim);
	strs = malloc((count + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	strs[count] = NULL;
	count = 0;
	i = 0;
	while (s[i])
	{
		j = i;
		while (s[i] && ft_strchr(delim, s[i]) == NULL)
			++i;
		strs[count] = malloc(((i - j) + 1) * sizeof(char));
		if (strs[count] == NULL)
			return (NULL);
		strs[count][i - j] = '\0';
		ft_memcpy(strs[count], s + j, (i - j) * sizeof(char));
		while (s[i] && ft_strchr(delim, s[i]))
			++i;
		++count;
	}
	return (strs);
}
