/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 05:43:14 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/23 23:33:47 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_mem.h"
#include <stdio.h>

static void	init_command(t_lexer_tok *cmd);
static int	is_split(t_lexer_tok *token);
static int	is_redirection(t_lexer_tok *token);

int	simplify_tokens(t_lexer *lexer)
{
	size_t		i;
	t_lexer_tok	cmd;
	t_lexer_tok	*token;
	t_redirection	redirection;
	t_lexer			new;

	init_lexer(&new);
	init_command(&cmd);
	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (is_split(token))
		{
			add_vector(&new, &cmd, 1);
			add_vector(&new, token, 1);
			init_command(&cmd);
		}
		else if (token->type == WORD)
		{
			dprintf(2, "aaa=%s\n", token->content);
			add_vector(&cmd.args, &token->content, 1);
		}
		else if (is_redirection(token))
		{
			redirection.type = token->type;
			remove_vector(lexer, i);
			token = at_vector(lexer, i);
			redirection.file = token->content;
			add_vector(&cmd.redirections, &redirection, 1);
		}
		else if (token->type == SUBSHELL)
		{
			add_vector(&new, token, 1);
		}
		remove_vector(lexer, i);
	}
	add_vector(&new, &cmd, 1);
	dprintf(2, "zizi\n\n");
	print_lexer(&new);
	return (0);
}

static void	init_command(t_lexer_tok *cmd)
{
	ft_memset(cmd, 0, sizeof(t_lexer_tok));
	cmd->type = COMMAND;
	init_vector(&cmd->args, sizeof(char *));
	init_vector(&cmd->redirections, sizeof(t_redirection));
}

static int	is_split(t_lexer_tok *token)
{
	return (token->type == LOGICAL_OR
			|| token->type == LOGICAL_AND
			|| token->type == PIPE);
}

static int	is_redirection(t_lexer_tok *token)
{
	return (token->type == HERE_DOC
			|| token->type == REDIRECT_IN
			|| token->type == REDIRECT_OUT
			|| token->type == APPEND);
}
