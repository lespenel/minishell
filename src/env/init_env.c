/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:55:53 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 05:33:21 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"
#include "hashmap.h"
#include "ft_char.h"
#include "ft_io.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	add_variable(t_env *env, char *str);
static int	set_shlvl(t_env *env);
static int	set_pwd(t_env *env);
static int	get_shvalue(char *nptr);

int	init_env(t_env *env, char *envp[])
{
	init_hashmap(env);
	while (*envp)
	{
		if (add_variable(env, *envp) == -1)
		{
			destroy_env(env);
			return (-1);
		}
		++envp;
	}
	if (set_shlvl(env) == -1)
	{
		destroy_env(env);
		return (-1);
	}
	if (set_pwd(env) == -1)
	{
		destroy_env(env);
		return (-1);
	}
	return (0);
}

static int	add_variable(t_env *env, char *str)
{
	char	*currentvar;
	char	*value;

	currentvar = ft_strdup(str);
	if (currentvar == NULL)
		return (-1);
	value = ft_strtok(currentvar, "=");
	value = ft_strtok(NULL, "=");
	if (value)
	{
		if (ms_setenv(env, currentvar, value) == -1)
		{
			free(currentvar);
			return (-1);
		}
	}
	free(currentvar);
	return (0);
}

static int	set_shlvl(t_env *env)
{
	char	*shlvl;
	int		shvalue;

	shlvl = ms_getenv(env, "SHLVL");
	if (shlvl == NULL)
		return (ms_setenv(env, "SHLVL", "1"));
	shvalue = get_shvalue(shlvl);
	shlvl = ft_itoa(shvalue);
	if (shlvl == NULL)
		return (-1);
	if (shvalue >= 1000)
	{
		ft_dprintf(2, SHLVL_TOO_HIGH, shlvl);
		free(shlvl);
		return (ms_setenv(env, "SHLVL", "1"));
	}
	if (ms_setenv(env, "SHLVL", shlvl) == -1)
	{
		free(shlvl);
		return (-1);
	}
	free(shlvl);
	return (0);
}

static int	set_pwd(t_env *env)
{
	char	*pwd;

	if (ms_getenv(env, "PWD") != NULL)
		return (0);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (errno == ENOMEM);
	if (ms_setenv(env, "PWD", pwd) == -1)
	{
		free(pwd);
		return (-1);
	}
	free(pwd);
	return (0);
}

static int	get_shvalue(char *nptr)
{
	int	shvalue;

	shvalue = ft_atoi(nptr);
	if (shvalue == INT_MAX)
		--shvalue;
	++shvalue;
	if (shvalue < 0)
		shvalue = 0;
	return (shvalue);
}
