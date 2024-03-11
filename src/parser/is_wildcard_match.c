/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wildcard_match.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:11:46 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/11 08:25:34 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static	int	handle_wildcard(char **motif, char **f_name);
static	int	the_end_match(char *motif, char *f_name);
static	int	the_last_wildcard(char *motif, char *f_name);

int	is_wildcard_match(char	*motif, char *f_name)
{
	while (*motif && *f_name)
	{
		if (*motif == '*')
		{
			if (handle_wildcard(&motif, &f_name))
				return (1);
		}
		else if (*motif == *f_name)
		{
			++f_name;
			++motif;
		}
		else
			return (0);
	}
	if (the_end_match(motif, f_name))
		return (1);
	else if (the_last_wildcard(motif, f_name))
		return (1);
	return (0);
}

static	int	handle_wildcard(char **motif, char **f_name)
{
	while (**motif == '*')
		*motif += 1;
	if (**motif == '\0')
		return (1);
	while (**f_name && **f_name != **motif)
		*f_name += 1;
	return (0);
}

static	int	the_end_match(char *motif, char *f_name)
{
	if (*motif == '\0' && *f_name)
	{
		while (*f_name)
			++f_name;
		while (*f_name == *motif)
		{
			--motif;
			--f_name;
		}
		if (*motif == '*')
			return (1);
	}
	return (0);
}

static	int	the_last_wildcard(char *motif, char *f_name)
{
	if (*motif == '*' && *f_name == '\0')
	{
		if (motif[1] == '\0')
			return (1);
	}
	if (*motif == '\0' && *f_name == '\0')
		return (1);
	return (0);
}
