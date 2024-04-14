/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 03:40:03 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/14 19:49:56 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_io.h"
#include "ft_string.h"
#include <errno.h>
#include <stdlib.h>

static char	*get_var_name(char *str);

int	ms_export(t_env *env, char **args)
{
	char	*var_name;
	int		i;

	i = 1;
	while (args[i])
	{
		var_name = get_var_name(args[i]);
		if (var_name == NULL)
			return (errno != 0);
		if (is_valid_identifier(var_name) == 0)
		{
			free(var_name);
			ft_dprintf(2, EXPORT_ID, args[i]);
			return (1);
		}
		if (ms_setenv(env, var_name, ft_strchr(args[i], '=') + 1) == -1)
		{
			free(var_name);
			return (1);
		}
		free(var_name);
		++i;
	}
	return (0);
}

static char	*get_var_name(char *str)
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
