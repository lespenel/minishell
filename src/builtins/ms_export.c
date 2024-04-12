/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 03:40:03 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/12 08:33:02 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_io.h"
#include "ft_string.h"
#include <stdlib.h>

static char	*get_var_name(char *str);

int	ms_export(t_env *env, char **args)
{
	char	*var_name;
	int		i;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]) == 0 || args[i][0] == '=')
		{
			ft_dprintf(2, EXPORT_ID, args[i]);
			return (1);
		}
		if (ft_strchr(args[i], '=') == NULL)
			return (0);
		var_name = get_var_name(args[i]);
		if (var_name == NULL)
			return (1);
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
