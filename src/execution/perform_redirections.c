/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 05:46:57 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/02 07:15:07 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "fcntl.h"
#include <stdio.h>
#include <unistd.h>

static int	perform_redirection(t_redirection *redirection);

int	perform_redirections(t_lexer_tok *token)
{
	size_t	i;
	int		ret;

	i = 0;
	while (i < token->redirections.size)
	{
		ret = perform_redirection(at_vector(&token->redirections, i));
		if (ret == -1)
			return (-1);
		if (ret == 1)
			dprintf(2, "open error, to handle\n");
		++i;
	}
	return (0);
}

static int	perform_redirection(t_redirection *redirection)
{
	int	fd;

	if (redirection->type == REDIRECT_IN)
	{
		fd = open(redirection->file, O_RDONLY);
		if (fd == -1)
			return (1);
		if (dup2(fd, 0) == -1)
			return (-1);
		return (0);
	}
	else if (redirection->type == APPEND)
		fd = open(redirection->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(redirection->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	if (dup2(fd, 1) == -1)
		return (-1);
	return (0);
}
