/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 08:23:20 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 04:24:03 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "env.h"
#include "ft_string.h"
#include "minishell.h"
#include "vector.h"
#include "prompt.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	fill_prompt(t_ms *ms, t_vector *prompt);
static int	do_simple_prompt(t_ms *ms);
static int	add_exitcode(t_ms *ms, t_vector *prompt);
static char	*getexitcodestr(t_ms *ms);

char	*get_prompt(t_ms *ms)
{
	t_vector	prompt;

	if (do_simple_prompt(ms))
		return (ft_strdup(PROMPT));
	init_vector(&prompt, sizeof(char));
	if (fill_prompt(ms, &prompt) == -1)
	{
		clear_vector(&prompt);
		return (NULL);
	}
	if (add_vector(&prompt, " > ", 3) == -1)
	{
		clear_vector(&prompt);
		return (NULL);
	}
	if (add_color_to_prompt(&prompt, RESET_COLOR) == -1)
		return (NULL);
	return (prompt.array);
}

static int	fill_prompt(t_ms *ms, t_vector *prompt)
{
	if (add_pwd(ms, prompt) == -1)
		return (-1);
	if (get_git_branch(ms, prompt) == -1)
		return (-1);
	if (add_exitcode(ms, prompt) == -1)
		return (-1);
	if (add_color_to_prompt(prompt, BHWHT) == -1)
		return (-1);
	return (0);
}

static int	do_simple_prompt(t_ms *ms)
{
	if (isatty(STDIN_FILENO) == 0
		|| isatty(STDOUT_FILENO) == 0
		|| isatty(STDERR_FILENO) == 0)
		return (1);
	return (ms_getenv(&ms->env, "TERM") == NULL);
}

static int	add_exitcode(t_ms *ms, t_vector *prompt)
{
	char	*exitcodestr;

	if (ms->lastexit == 0)
		return (0);
	if (add_color_to_prompt(prompt, RED) == -1)
		return (-1);
	if (add_vector(prompt, " [", 2) == -1)
		return (-1);
	if (add_color_to_prompt(prompt, BHRED) == -1)
		return (-1);
	exitcodestr = getexitcodestr(ms);
	if (add_vector(prompt, exitcodestr, ft_strlen(exitcodestr)) == -1)
		return (-1);
	if (add_color_to_prompt(prompt, RED) == -1)
		return (-1);
	if (add_vector(prompt, "]", 1) == -1)
		return (-1);
	if (add_color_to_prompt(prompt, RESET_COLOR) == -1)
		return (-1);
	return (0);
}

static char	*getexitcodestr(t_ms *ms)
{
	static char	*signals[] = {[SIGHUP] = "SIGHUP", [SIGINT] = "SIGINT",
	[SIGQUIT] = "SIGQUIT", [SIGILL] = "SIGILL", [SIGTRAP] = "SIGTRAP",
	[SIGABRT] = "SIGABRT", [SIGBUS] = "SIGBUS", [SIGFPE] = "SIGFPE",
	[SIGKILL] = "SIGKILL", [SIGUSR1] = "SIGUSR1", [SIGSEGV] = "SIGSEGV",
	[SIGUSR2] = "SIGUSR2", [SIGPIPE] = "SIGPIPE", [SIGALRM] = "SIGALRM",
	[SIGTERM] = "SIGTERM", [SIGSTKFLT] = "SIGSTKFLT", [SIGCHLD] = "SIGCHLD",
	[SIGCONT] = "SIGCONT", [SIGSTOP] = "SIGSTOP", [SIGTSTP] = "SIGTSTP",
	[SIGTTIN] = "SIGTTIN", [SIGTTOU] = "SIGTTOU", [SIGURG] = "SIGURG",
	[SIGXCPU] = "SIGXCPU", [SIGXFSZ] = "SIGXFSZ", [SIGVTALRM] = "SIGVTALRM",
	[SIGPROF] = "SIGPROF", [SIGWINCH] = "SIGWINCH", [SIGIO] = "SIGIO",
	[SIGPWR] = "SIGPWR"};

	if (ms->lastexit >= 129 && ms->lastexit <= 158)
		return (signals[ms->lastexit - 128]);
	return (ms->lastexitstr);
}
