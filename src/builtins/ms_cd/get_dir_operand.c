/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_operand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 04:40:51 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/10 00:32:33 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_io.h"
#include "builtins.h"
#include "builtins/ms_cd.h"

static	char	*get_home(t_env *env);
static	char	*get_oldpwd(t_env *env);

char	*get_dir_operand(t_env *env, char **args)
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
			dir_operand = get_oldpwd(env);
		else
			dir_operand = ft_strdup(args[1]);
	}
	return (dir_operand);
}

static char	*get_home(t_env *env)
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

static	char	*get_oldpwd(t_env *env)
{
	char	*oldpwd;

	oldpwd = ms_getenv(env, "OLDPWD");
	if (oldpwd == NULL)
	{
		ft_dprintf(2, OLDPWD_NOT_SET);
		return (NULL);
	}
	if (ft_dprintf(1, "%s\n", oldpwd) == -1)
		return (NULL);
	oldpwd = ft_strdup(oldpwd);
	return (oldpwd);
}
