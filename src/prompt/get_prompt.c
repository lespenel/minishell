/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 08:23:20 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/13 06:35:03 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "env.h"
#include "ft_string.h"
#include "minishell.h"
#include "vector.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	do_simple_prompt(void);
static int	add_exitcode(t_ms *ms, t_vector *prompt);
static int	get_git_branch(t_ms *ms, t_vector *prompt);
static int	add_git_branch(t_vector *prompt, char *branch);
static int	add_pwd(t_ms *ms, t_vector *prompt);

char	*get_prompt(t_ms *ms)
{
	t_vector	prompt;

	if (do_simple_prompt())
		return (ft_strdup(PROMPT));
	init_vector(&prompt, sizeof(char));
	if (add_pwd(ms, &prompt) == -1)
	{
		clear_vector(&prompt);
		return (NULL);
	}
	if (get_git_branch(ms, &prompt) == -1)
	{
		clear_vector(&prompt);
		return (NULL);
	}
	if (add_exitcode(ms, &prompt) == -1)
	{
		clear_vector(&prompt);
		return (NULL);
	}
	if (add_color_to_prompt(&prompt, BHWHT) == -1)
		return (NULL);
	if (add_vector(&prompt, " 8==================> ", 22) == -1)
	{
		clear_vector(&prompt);
		return (NULL);
	}
	if (add_color_to_prompt(&prompt, RESET_COLOR) == -1)
		return (NULL);
	return (prompt.array);
}

static int	do_simple_prompt(void)
{
	if (isatty(STDIN_FILENO) == 0
		|| isatty(STDOUT_FILENO) == 0
		|| isatty(STDERR_FILENO) == 0)
		return (1);
	return (0);
}

static int	add_exitcode(t_ms *ms, t_vector *prompt)
{
	if (ms->lastexit == 0)
		return (0);
	if (add_color_to_prompt(prompt, RED) == -1)
		return (-1);
	if (add_vector(prompt, " [", 2) == -1)
		return (-1);
	if (add_color_to_prompt(prompt, BHRED) == -1)
		return (-1);
	if (add_vector(prompt, ms->lastexitstr, ft_strlen(ms->lastexitstr)) == -1)
		return (-1);
	if (add_color_to_prompt(prompt, RED) == -1)
		return (-1);
	if (add_vector(prompt, "]", 1) == -1)
		return (-1);
	if (add_color_to_prompt(prompt, RESET_COLOR) == -1)
		return (-1);
	return (0);
}

static int	get_git_branch(t_ms *ms, t_vector *prompt)
{
	static char	*argv[] = {"git", "branch", "--show-current", NULL};
	char		*result;

	result = get_command_result(ms, argv);
	if (result == NULL)
		return (-1);
	if (add_git_branch(prompt, result) == -1)
	{
		free(result);
		return (-1);
	}
	free(result);
	return (0);
}

static int	add_git_branch(t_vector *prompt, char *branch)
{
	if (ft_strlen(branch) == 0)
		return (0);
	if (add_color_to_prompt(prompt, WHT) == -1)
		return (-1);
	if (add_vector(prompt, " (", 2) == -1)
		return (-1);
	if (add_color_to_prompt(prompt, WHT) == -1)
		return (-1);
	if (add_vector(prompt, branch, ft_strlen(branch) - 1) == -1)
		return (-1);
	if (add_color_to_prompt(prompt, WHT) == -1)
		return (-1);
	if (add_vector(prompt, ")", 1) == -1)
		return (-1);
	if (add_color_to_prompt(prompt, RESET_COLOR) == -1)
		return (-1);
	return (0);
}

static int	add_pwd(t_ms *ms, t_vector *prompt)
{
	const char	*pwd = ms_getenv(&ms->env, "PWD");
	const char	*home = ms_getenv(&ms->env, "HOME");

	if (pwd == NULL)
	{
		pwd = getcwd(NULL, 0);
	}
	else
		pwd = ft_strdup(pwd);
	// todo : handle
	if (pwd == NULL)
		return (0);
	if (add_color_to_prompt(prompt, BHGRN) == -1)
		return (-1);
	if (home)
	{
		if (ft_strncmp(pwd, home, ft_strlen(home)) == 0)
		{
			if (add_vector(prompt, "~", 1) == -1)
				return (-1);
			if (add_vector(prompt, pwd + ft_strlen(home), ft_strlen(pwd + ft_strlen(home))) == -1)
				return (-1);
		}
		else
		{
			if (add_vector(prompt, pwd, ft_strlen(pwd)) == -1)
				return (-1);
		}
	}
	else
	{
		if (add_vector(prompt, pwd, ft_strlen(pwd)) == -1)
			return (-1);
	}
	if (add_color_to_prompt(prompt, RESET_COLOR) == -1)
		return (-1);
	return (0);
}
