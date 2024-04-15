/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 02:42:46 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 05:56:21 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "util.h"
#include "signals.h"
#include "prompt.h"
#include "execution.h"
#include "vector.h"
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>

static int	handle_input(t_ms *ms, char *input);
static char	*get_line(t_ms *ms);
static int	execute_sh_cmd(t_ms *ms, t_lexer *lexer);

int	run_shell(t_ms *ms)
{
	char	*input;
	int		ret;

	input = get_line(ms);
	while (input)
	{
		ret = handle_input(ms, input);
		free(input);
		if (ret == -1)
			return (-1);
		if (ret == 1 && set_exitcode_str(ms, 2) == -1)
			return (-1);
		if (g_sig == SIGINT)
		{
			if (set_exitcode_str(ms, 128 + SIGINT) == -1)
				return (-1);
			g_sig = 0;
		}
		input = get_line(ms);
	}
	return ((errno == 0) - 1);
}

static int	handle_input(t_ms *ms, char *input)
{
	t_lexer	lexer;
	int		ret;

	ret = parse_input(ms, &lexer, input);
	if (ret || g_sig == SIGINT)
	{
		clear_lexer_unlink(&lexer);
		return (ret);
	}
	if (lexer.size == 1)
	{
		clear_lexer_unlink(&lexer);
		return (0);
	}
	if (execute_sh_cmd(ms, &lexer) == -1)
	{
		clear_lexer_unlink(&lexer);
		return (-1);
	}
	clear_lexer_unlink(&lexer);
	return (0);
}

static char	*get_line(t_ms *ms)
{
	char	*prompt;
	char	*input;

	errno = 0;
	input = NULL;
	while (input == NULL)
	{
		prompt = get_prompt(ms);
		if (prompt == NULL)
			return (NULL);
		input = readline(prompt);
		free(prompt);
		if (g_sig == SIGINT)
		{
			free(input);
			input = NULL;
			if (set_exitcode_str(ms, 128 + SIGINT) == -1)
				return (NULL);
			g_sig = 0;
		}
		else if (input == NULL)
			return (NULL);
	}
	return (input);
}

static int	execute_sh_cmd(t_ms *ms, t_lexer *lexer)
{
	if (execution_structure(lexer) == -1)
		return (-1);
	if (execute_commands_interactive(ms, lexer) == -1)
		return (-1);
	return (0);
}
