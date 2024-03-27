/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_filenames.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:41:39 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/27 14:59:59 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "wildcard.h"
#include "lexer.h"

static size_t	array_partition(t_lexer *filenames, ssize_t start, ssize_t end);
static void		swap_token(t_lexer_tok *t1, t_lexer_tok *t2);
static int		ms_strcmp(char *s1, char *s2);
static int		ft_tolower(int c);

void	sort_filenames(t_lexer *filenames, ssize_t start, ssize_t end)
{
	ssize_t	pivot_index;

	if (start < end)
	{
		pivot_index = array_partition(filenames, start, end);
		sort_filenames(filenames, start, pivot_index - 1);
		sort_filenames(filenames, pivot_index + 1, end);
	}
}

static size_t	array_partition(t_lexer *filenames, ssize_t start, ssize_t end)
{
	char		*pivot;
	ssize_t		i;
	ssize_t		j;
	t_lexer_tok	*tok;

	i = start;
	j = start;
	tok = at_vector(filenames, end);
	pivot = tok->content;
	while (i < end)
	{
		tok = at_vector(filenames, i);
		if (ms_strcmp(tok->content, pivot) <= 0)
		{
			swap_token(at_vector(filenames, j), tok);
			++j;
		}
		++i;
	}
	swap_token(at_vector(filenames, j), at_vector(filenames, end));
	return (j);
}

static	int	ms_strcmp(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i] && ft_tolower(s1[i]) == ft_tolower(s2[i]))
		++i;
	if (ft_tolower(s1[i]) == ft_tolower(s2[i]))
	{
		j = 0;
		while (s1[j] && s1[j] == s2[j])
			++j;
		return (s2[j] - s1[j]);
	}
	return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
}

static	void	swap_token(t_lexer_tok *t1, t_lexer_tok *t2)
{
	t_lexer_tok	temp;

	temp.content = t1->content;
	temp.type = t1->type;
	t1->content = t2->content;
	t1->type = t2->type;
	t2->content = temp.content;
	t2->type = temp.type;
}

static int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
