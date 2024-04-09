/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:36:40 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 06:17:54 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"

int	is_builtin(char *word)
{
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

	i = 0;
	while (i <= EXIT)
	{
		if (ft_strcmp(word, builtins[i]) == 0)
			return (1);
		++i;
	}
	return (0);
}
