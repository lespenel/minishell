/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 05:38:10 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/15 05:25:58 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static int	case_cmp(char *s1, char *s2);
static int	ft_tolower(int c);
static int	no_case_cmp(char *s1, char *s2);

int	ms_strcmp(char *s1, char *s2)
{
	int	ret;

	ret = no_case_cmp(s1, s2);
	if (ret)
		return (ret);
	return (case_cmp(s1, s2));
}

static int	no_case_cmp(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j])
	{
		if (s1[i] == '.' || s1[i] == '/')
			++i;
		else if (s2[j] == '.' || s2[j] == '/')
			++j;
		else if (ft_tolower(s1[i]) == ft_tolower(s2[j]))
		{
			++i;
			++j;
		}
		else
			return (ft_tolower(s1[i]) - ft_tolower(s2[j]));
	}
	return (0);
}

static int	case_cmp(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j])
	{
		if (s1[i] == '.' || s1[i] == '/')
			++i;
		else if (s2[j] == '.' || s2[j] == '/')
			++j;
		else if (s1[i] == s2[j])
		{
			++i;
			++j;
		}
		else
			return (s1[i] - s2[j]);
	}
	return (ft_strcmp(s1, s2));
}

static int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
