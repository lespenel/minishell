/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 03:40:03 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/18 05:45:44 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_string.h"
#include <stdlib.h>

static char	*get_var_name(char *str);

int	ms_export(t_env *env, char **args)
{
	const int		argc = get_argc(args);
	char			*var_name;
	char			*equal_ptr;

	if (argc > 1)
	{
		equal_ptr = ft_strchr(args[1], '=');
		if (equal_ptr == NULL)
			return (0);
		var_name = get_var_name(args[1]);
		if (var_name == NULL)
			return (-1);
		if (ms_setenv(env, var_name, ft_strchr(args[1], '=') + 1) == -1)
		{
			free(var_name);
			return (-1);
		}
		free(var_name);
	}
	return (0);
}

static char	*get_var_name(char *str)
{
	size_t	i;
	char	*var_name;

	i = 0;
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
