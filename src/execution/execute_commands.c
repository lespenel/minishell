/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:20:04 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/25 06:50:39 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "vector.h"
#include "ft_string.h"
#include "execution.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


//static int	execute_pipeline(t_ms *ms, t_lexer *lexer);
static int	execute_single_command(t_ms *ms, t_lexer *lexer, size_t i);

int	execute_commands(t_ms *ms, t_lexer *lexer)
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	print_lexer(lexer);
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == COMMAND)
			execute_single_command(ms, lexer, i);
		++i;
	}
	(void)ms;
	return (0);
}

static int	execute_single_command(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;
	char		*path;

	(void)ms;
	token = at_vector(lexer, i);
	if (fork() == 0)
	{
		if (perform_redirections(token) == -1)
			return (-1);
		path = *((char **)at_vector(&token->args, 0));
		if (ft_strchr(path, '/') == NULL)
			path = get_path(ms, *((char **)at_vector(&token->args, 0)));
		if (path == NULL)
			exit(-1);
		execv(path, token->args.array);
		exit(0);
	}
	wait(NULL);
	return (0);
}

//static int	execute_pipeline(t_ms *ms, t_lexer *lexer)
//{
//
//}
