/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:04:00 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/13 17:11:38 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "env.h"
#include "minishell.h"
#include "prompt.h"
#include "ft_string.h"
#include "vector.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int	add_pwd_content(t_vector *prompt, char *pwd, char *home);

int	add_pwd(t_ms *ms, t_vector *prompt)
{
	char	*pwd;

	pwd = ms_getenv(&ms->env, "PWD");
	if (pwd == NULL)
		pwd = getcwd(NULL, 0);
	else
		pwd = ft_strdup(pwd);
	if (pwd == NULL)
	{
		if (errno == ENOMEM)
			return (-1);
		return (0);
	}
	if (add_pwd_content(prompt, pwd, ms_getenv(&ms->env, "HOME")) == -1)
	{
		free(pwd);
		return (-1);
	}
	free(pwd);
	if (add_color_to_prompt(prompt, RESET_COLOR) == -1)
		return (-1);
	return (0);
}

static int	add_pwd_content(t_vector *prompt, char *pwd, char *home)
{
	const size_t	pwd_len = ft_strlen(pwd);
	size_t			home_len;

	if (add_color_to_prompt(prompt, BHGRN) == -1)
		return (-1);
	if (home)
	{
		home_len = ft_strlen(home);
		if (ft_strncmp(pwd, home, home_len) == 0)
		{
			if (add_vector(prompt, "~", 1) == -1)
				return (-1);
			if (add_vector(prompt, pwd + home_len, pwd_len - home_len) == -1)
				return (-1);
		}
		else
		{
			if (add_vector(prompt, pwd, pwd_len) == -1)
				return (-1);
		}
	}
	else if (add_vector(prompt, pwd, pwd_len) == -1)
		return (-1);
	return (0);
}
