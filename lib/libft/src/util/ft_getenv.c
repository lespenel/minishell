/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:30:21 by ccouble           #+#    #+#             */
/*   Updated: 2024/01/01 11:16:24 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <stdio.h>

char	*ft_getenv(char *envp[], char *name)
{
	size_t	i;

	while (*envp)
	{
		i = 0;
		while (envp[0][i] == name[i] && envp[0][i])
		{
			++i;
		}
		if (envp[0][i] == '=' && name[i] == '\0')
			return (*envp + i + 1);
		++envp;
	}
	return (NULL);
}
