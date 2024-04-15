/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:43:05 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/15 06:43:51 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ft_io.h"
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
	ft_dprintf(1, "\n");
	while (i < token_tab->size)
	{
		token = at_vector(token_tab, i);
		if (token->type == SUBSHELL)
			print_subshell(token);
		else if (token->type == COMMAND)
			print_command(token);
		else if (ft_dprintf(1, "content = %-10s | token = %d\n",
				token->content, token->type) == -1)
			return (-1);
		i++;
	}
	ft_dprintf(1, "\n");
	return (0);
}

static void	print_subshell(t_lexer_tok *token)
{
	ft_dprintf(1, "ENTER  SUBSHELL !!\n");
	print_lexer(&token->subshell);
	ft_dprintf(1, "EXIT  SUBSHELL !!\n");
}

static void	print_command(t_lexer_tok *token)
{
	size_t			i;
	char			**s;
	t_redirection	*redirection;

	ft_dprintf(1, "enter command\n");
	i = 0;
	while (i < token->args.size)
	{
		s = at_vector(&token->args, i);
		ft_dprintf(1, "args[%ld]=%s\n", i, *s);
		++i;
	}
	i = 0;
	while (i < token->redirections.size)
	{
		redirection = at_vector(&token->redirections, i);
		ft_dprintf(1, "redir[%ld]={type=%d, file=%s}\n", i, redirection->type,
			redirection->file);
		++i;
	}
	ft_dprintf(1, "exit command\n");
}
