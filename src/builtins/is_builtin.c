/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:36:40 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/17 04:20:25 by lespenel         ###   ########.fr       */
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
		if (ft_strncmp(word, builtins[i], ft_strlen(word)) == 0)
			return (1);
		++i;
	}
	return (0);
}
