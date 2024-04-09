/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_nq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 03:09:00 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/06 06:44:19 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "ft_string.h"
#include "util.h"
#include "expander.h"
#include <stdio.h>
#include <stdlib.h>

static int	check_full_ifs(char *s, const char *ifs);
static int	prepare_ifs(t_vector *tab, t_vector *new, char *s, const char *ifs);

ssize_t	expand_nq(t_ms *ms, t_vector *tab, t_vector *new, char *value)
{
	const char	*ifs = get_ifs(&ms->env);
	int			end_ifs;

	if (check_full_ifs(value, ifs) == 1)
		return (0);
	end_ifs = prepare_ifs(tab, new, value, ifs);
	if (end_ifs == -1)
		return (-1);
	if (fill_nq_var(tab, new, value, ifs) == -1)
		return (-1);
	if (end_ifs)
		return (add_word_tab(tab, new));
	return (0);
}

static int	check_full_ifs(char *s, const char *ifs)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_strchr(ifs, s[i]))
		++i;
	return (i == ft_strlen(s));
}

static int	prepare_ifs(t_vector *tab, t_vector *new, char *s, const char *ifs)
{
	size_t	len;

	len = ft_strlen(s);
	if (len == 0)
		return (0);
	if (new->size != 0 && ft_strchr(ifs, s[0]))
	{
		if (add_word_tab(tab, new) == -1)
			return (-1);
	}
	return (ft_strchr(ifs, s[len - 1]) != NULL);
}
