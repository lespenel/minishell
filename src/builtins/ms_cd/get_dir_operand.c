/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_operand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel </var/spool/mail/lespenel>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 04:40:51 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 04:05:38 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"
#include "ft_io.h"
#include "builtins.h"
#include <stdlib.h>

static	char *get_home(t_env *env);

char *get_dir_operand(t_env *env, char **args)
{
	const int	argc = get_argc(args);
	char		*dir_operand;

	if (argc > 2)
	{
		ft_dprintf(2, TOO_MANY_ARGS);
		return (NULL);
	}
	if (argc == 1)
		dir_operand = get_home(env);
	else 
	{
		if (ft_strcmp(args[1], "-") == 0)
		{
			dir_operand = ms_getenv(env, "OLDPWD");
			if (dir_operand == NULL)
				return (NULL);
			dir_operand = ft_strdup(dir_operand);
		}
		else
			dir_operand = ft_strdup(args[1]);
	}
	if (dir_operand == NULL)
			return (NULL);
	return (dir_operand);
}

static	char *get_home(t_env *env)
{
	char	*home;

	home = ms_getenv(env, "HOME");
	if (home == NULL)
	{
		ft_dprintf(2, HOME_NOT_SET);
			return (NULL);
	}
	home = ft_strdup(home);
	if (home == NULL)
		return (NULL);
	return (home);
}
