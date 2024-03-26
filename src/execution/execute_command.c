/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:14:46 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/26 06:15:45 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "execution.h"
#include "ft_string.h"
#include <stdlib.h>
#include <unistd.h>

int	execute_command(t_ms *ms, t_lexer_tok *token)
{
	char	*path;

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
