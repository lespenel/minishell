/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:59:18 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/20 01:33:30 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_string.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static	int		go_to_home(t_env *env);
static	char	*remove_end_slash(char *path);
static	char 	*remove_dot(char *path);

int	ms_cd(t_env	*env, char **args)
{
	const int	argc = get_argc(args);
	char		*path;

	if (argc > 2)
	{
		dprintf(2, "cd: too many arguments");
		return (1);
	}
	if (argc == 1)
	{
		if (go_to_home(env) == -1)
			return (-1);
		return (0);
	}
	else
	{
		if (args[1][0] != '/')
		{
			if (ft_strncmp(args[1], "./", ft_strlen(args[1])) == 0)
				return (printf("bite\n"));
			if (ft_strncmp(args[1], "../", ft_strlen(args[1])) == 0)
			{
				printf("sexe\n");
			}
			path = getcwd(NULL, 0);
			if (path == NULL)
				return (-1);
			path = ft_strjoin_three(path, "/", args[argc - 1]);
			if (path == NULL)
				return (-1);
			printf("path = %s\n", path);
		}
		else
			path = args[1];
	}
	path = remove_end_slash(path);
	if (path == NULL)
		return (-1);
	path = remove_dot(path);
	if (path == NULL)
		return (-1);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (-1);
	}
	if (ms_setenv(env, "PWD", path) == -1)
		return (-1);
	return (0);
}

static	int	go_to_home(t_env *env)
{
	char *path;

	path = ms_getenv(env, "HOME");
	if (path == NULL)
		return (-1);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (-1);
	}
	if (ms_setenv(env, "PWD", path) == -1)
		return (-1);
	return (0);
}

static	char	*remove_end_slash(char *str)
{
	size_t	len;
	char *new_path;

	len = 0;
	while (str[len])
		++len;
	while (str[len - 1] == '/')
		--len;
	new_path = malloc(sizeof(char) * len + 1);
	if (new_path == NULL)
		return (NULL);
	ft_strncpy(new_path, str, len);
	new_path[len] = '\0';
	printf("path = %s\n", new_path);
	free(str);
	return (new_path);
}

static	char *remove_dot(char *str)
{
	size_t	len;
	char	*path;

	len = 0;
	while (str[len])
		++len;
	path = str;
	if (ft_strcmp(str + len - 2, "..") == 0)
	{
		printf("oui il ya ..\n");
		len -= 4;
		printf("len = %ld, str[len] == %c\n", len, str[len]);
		while (len > 1 && str[len] != '/')
			--len;
		printf("new len == %d, str[nlen] = %c\n", (int)len, str[len]);
		path = malloc(sizeof(char) * len + 1);
		if (path == NULL)
			return (NULL);
		ft_strncpy(path, str, len);
		path[len] = '\0';
		printf("remove dot path == %s\n", path);
		path = str;
	}
	return (path);
}
