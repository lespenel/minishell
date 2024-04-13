/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:57:58 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/13 18:00:35 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_string.h"
#include "parser.h"
#include "signals.h"
#include "vector.h"
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <readline/history.h>
#include <stdio.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static int	write_to_vect(t_vector *vect, char *limit);
static char	*here_doc_rl(void);

int	fill_here_doc(t_ms *ms, t_vector *vector, char *path, t_lexer_tok *limit)
{
	t_vector	new;
	int			fd;

	if (write_to_vect(vector, limit->content) == -1)
		return (-1);
	if (g_sig == SIGINT)
		return (0);
	init_vector(&new, sizeof(char));
	if (add_here_doc_str(ms, &new, vector->array) == -1)
	{
		clear_vector(&new);
		return (-1);
	}
	fd = get_tempfile(path);
	if (fd == -1)
		return (-1);
	if (write(fd, new.array, new.size) == -1)
	{
		clear_vector(&new);
		close(fd);
		return (-1);
	}
	clear_vector(&new);
	close(fd);
	return (0);
}

static int	write_to_vect(t_vector *vect, char *limit)
{
	char	*input;
	char	*str_with_nl;

	input = here_doc_rl();
	while (input && ft_strcmp(input, limit))
	{
		if (g_sig == SIGINT)
			return (0);
		str_with_nl = ft_strjoin(input, "\n");
		free(input);
		if (str_with_nl == NULL)
			return (-1);
		if (add_vector(vect, str_with_nl, ft_strlen(str_with_nl)) == -1)
		{
			free(str_with_nl);
			return (-1);
		}
		free(str_with_nl);
		input = here_doc_rl();
	}
	if (input)
		free(input);
	return ((errno == 0) - 1);
}

static char	*here_doc_rl(void)
{
	char	*input;

	input = NULL;
	while (input == NULL)
	{
		input = readline("> ");
		if (g_sig == SIGINT)
		{
			if (input)
				free(input);
			return (NULL);
		}
	}
	return (input);
}
