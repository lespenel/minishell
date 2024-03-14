/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_filenames.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 08:41:39 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/14 09:32:44 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "wildcard.h"
#include "lexer.h"

static void		swap_token(t_lexer_tok *t1, t_lexer_tok *t2);
static int		ft_tolower(int c);
static int		ms_strcmp(char *s1, char *s2);

void	sort_filenames(t_lexer *filenames)
{
	size_t		i;
	size_t		j;
	t_lexer_tok	*t1;
	t_lexer_tok	*t2;

	i = 0;
	if (filenames->size < 1)
		return ;
	while (i < filenames->size - 1)
	{
		j = 0;
		while (j < filenames->size - 1)
		{
			t1 = at_vector(filenames, j);
			t2 = at_vector(filenames, j + 1);
			if (ms_strcmp(t1->content, t2->content) > 0)
				swap_token(t1, t2);
			++j;
		}
		++i;
	}
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
			j++;
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
