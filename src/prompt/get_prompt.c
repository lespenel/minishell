/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 08:23:20 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/09 08:46:12 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "minishell.h"
#include <unistd.h>

static int	do_simple_prompt();

char	*get_prompt()
{
	char	*prompt;

	if (do_simple_prompt())
		return (ft_strdup(PROMPT));
	
	return (NULL);
}

static int	do_simple_prompt()
{
	if (isatty(STDIN_FILENO) == 0
		|| isatty(STDOUT_FILENO) == 0
		|| isatty(STDERR_FILENO) == 0)
		return (1);
	return (0);
}
