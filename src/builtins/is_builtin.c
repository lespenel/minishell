/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:36:40 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/10 00:29:55 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include <stddef.h>

int	is_builtin(char *word)
{
	const size_t		len = ft_strlen(word);
	int					i;
	static const char	*builtins[] = {
	[ECHO] = "echo",
	[CD] = "cd",
	[PWD] = "pwd",
	[EXPORT] = "export",
	[UNSET] = "unset",
	[ENV] = "env",
	[EXIT] = "exit",
	};

	if (len == 0)
		return (0);
	i = 0;
	while (i <= EXIT)
	{
		if (ft_strncmp(word, builtins[i], len) == 0)
			return (1);
		++i;
	}
	return (0);
}
