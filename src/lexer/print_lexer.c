/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:43:05 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/23 23:37:35 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

static void	print_subshell(t_lexer_tok *token);
static void	print_command(t_lexer_tok *token);

int	print_lexer(t_lexer *token_tab)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	printf("\n");
	while (i < token_tab->size)
	{
		token = at_vector(token_tab, i);
		if (token->type == SUBSHELL)
			print_subshell(token);
		else if (token->type == COMMAND)
			print_command(token);
		else if (printf("content = %-10s | token = %d\n",
				token->content, token->type) == -1)
			return (-1);
		i++;
	}
	printf("\n");
	return (0);
}

static void	print_subshell(t_lexer_tok *token)
{
	printf("ENTER  SUBSHELL !!\n");
	print_lexer(&token->subshell);
	printf("EXIT  SUBSHELL !!\n");
}

static void	print_command(t_lexer_tok *token)
{
	size_t			i;
	char			**s;
	t_redirection	*redirection;

	printf("enter command\n");
	i = 0;
	while (i < token->args.size)
	{
		s = at_vector(&token->args, i);
		printf("args[%ld]=%s\n", i, *s);
		++i;
	}
	i = 0;
	while (i < token->redirections.size)
	{
		redirection = at_vector(&token->redirections, i);
		printf("redir[%ld]={type=%d, file=%s, fd=%d}\n", i, redirection->type, redirection->file, redirection->fd);
		++i;
	}
	printf("exit command\n");
}
