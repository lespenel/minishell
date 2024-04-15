/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 23:11:16 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 02:05:22 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_io.h"
#include "ft_string.h"
#include "minishell.h"
#include <errno.h>
#include <stdlib.h>

static char	*get_name(char *str);

int	ms_alias(t_ms *ms, char **args)
{
	char	*name;
	int		i;

	i = 1;
	while (args[i])
	{
		name = get_name(args[i]);
		if (name == NULL)
			return (errno != 0);
		if (is_valid_identifier(name) == 0)
		{
			free(name);
			ft_dprintf(2, EXPORT_ID, args[i]);
			return (1);
		}
		if (ms_setenv(&ms->aliases, name, ft_strchr(args[i], '=') + 1) == -1)
		{
			free(name);
			return (1);
		}
		free(name);
		++i;
	}
	return (0);
}

static char	*get_name(char *str)
{
	size_t	i;
	char	*var_name;

	i = 0;
	errno = 0;
	if (ft_strchr(str, '=') == NULL)
		return (NULL);
	while (str[i] && str[i] != '=')
		++i;
	if (str[i])
	{
		var_name = malloc(sizeof(char) * i + 1);
		if (var_name == NULL)
			return (NULL);
		ft_strncpy(var_name, str, i);
		var_name[i] = '\0';
		return (var_name);
	}
	return (NULL);
}
