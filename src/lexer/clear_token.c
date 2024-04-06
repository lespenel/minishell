/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 23:25:36 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/04 16:21:48 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include <stdlib.h>

static void	clear_subshell(t_lexer_tok *token);
static void	clear_command(t_lexer_tok *token);
static void	clear_redirection(t_redirection *redirection);

void	clear_token(t_lexer_tok *token)
{
	if (token->type == SUBSHELL)
		clear_subshell(token);
	else if (token->type == COMMAND)
		clear_command(token);
	else if (token->content)
	{
		free(token->content);
		token->type = 0;
	}
}

static void	clear_subshell(t_lexer_tok *token)
{
	clear_lexer(&token->subshell);
}

static void	clear_command(t_lexer_tok *token)
{
	size_t	i;

	if (token->content)
		free(token->content);
	i = 0;
	while (i < token->args.size)
	{
		free(*((char **)at_vector(&token->args, i)));
		++i;
	}
	clear_vector(&token->args);
	i = 0;
	while (i < token->redirections.size)
	{
		clear_redirection(at_vector(&token->redirections, i));
		++i;
	}
	clear_vector(&token->redirections);
}

static void	clear_redirection(t_redirection *redirection)
{
	free(redirection->file);
}
