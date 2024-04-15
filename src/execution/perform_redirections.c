/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:46:57 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 06:40:29 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "fcntl.h"
#include "util.h"
#include "ft_io.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

static int	perform_redirection(t_redirection *redirection);

int	perform_redirections(t_lexer_tok *token)
{
	size_t			i;
	int				ret;
	t_redirection	*redir;

	i = 0;
	while (i < token->redirections.size)
	{
		redir = at_vector(&token->redirections, i);
		ret = perform_redirection(redir);
		if (ret == -1)
			return (-1);
		if (ret == 1)
		{
			ft_dprintf(2, "minishell: %s: %s\n", redir->file, strerror(errno));
			return (1);
		}
		++i;
	}
	return (0);
}

static int	perform_redirection(t_redirection *redirection)
{
	int	fd;

	if (redirection->type == HERE_DOC || redirection->type == REDIRECT_IN)
	{
		fd = open(redirection->file, O_RDONLY);
		if (fd == -1)
			return (1);
		if (dup_and_close(fd, STDIN_FILENO) == -1)
			return (-1);
		if (redirection->type == HERE_DOC)
			unlink(redirection->file);
		return (0);
	}
	else if (redirection->type == APPEND)
		fd = open(redirection->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(redirection->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	if (dup_and_close(fd, STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}
