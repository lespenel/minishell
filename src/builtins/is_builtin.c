/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:36:40 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/14 23:24:11 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include <stddef.h>

int	is_builtin(char *word)
{
	int					i;
	static const char	*builtins[] = {
	[MS_ALIAS] = "alias",
	[MS_ECHO] = "echo",
	[MS_CD] = "cd",
	[MS_PWD] = "pwd",
	[MS_EXPORT] = "export",
	[MS_UNALIAS] = "unalias",
	[MS_UNSET] = "unset",
	[MS_ENV] = "env",
	[MS_EXIT] = "exit",
	};

	i = 0;
	while (i <= MS_EXIT)
	{
		if (ft_strcmp(word, builtins[i]) == 0)
			return (1);
		++i;
	}
	return (0);
}
