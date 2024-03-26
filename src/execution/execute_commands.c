/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:20:04 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/26 06:17:46 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "vector.h"
#include "ft_string.h"
#include "execution.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

static int			execute_single_command(t_ms *ms, t_lexer *lexer, size_t i);
static t_lex_type	next_operator(t_lexer *lexer, size_t i);
static size_t		next_command(t_lexer *lexer, size_t i);

int	execute_commands(t_ms *ms, t_lexer *lexer)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	print_lexer(lexer);
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (next_operator(lexer, i) == PIPE)
			execute_pipeline(ms, lexer, i);
		else if (token->type == COMMAND)
			execute_single_command(ms, lexer, i);
		i = next_command(lexer, i);
		if (i >= lexer->size)
			return (0);
		++i;
	}
	(void)ms;
	return (0);
}

static int	execute_single_command(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;
	pid_t		pid;

	(void)ms;
	token = at_vector(lexer, i);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		execute_command(ms, token);
	wait(NULL);
	return (0);
}

static t_lex_type	next_operator(t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;

	++i;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == LOGICAL_OR || token->type == LOGICAL_AND || token->type == PIPE)
			return (token->type);
		++i;
	}
	return (-1);
}

static size_t		next_command(t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;

	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == LOGICAL_AND || token->type == LOGICAL_OR)
			return (i);
		++i;
	}
	return (i);
}
