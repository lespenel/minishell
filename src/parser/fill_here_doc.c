/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:57:58 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/12 10:56:44 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_string.h"
#include "parser.h"
#include "vector.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <stdio.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static int	write_to_vect(t_vector *vect, char *limit);

int	fill_here_doc(t_ms *ms, t_vector *vector, char *path, t_lexer_tok *limit)
{
	t_vector	new;
	int			fd;

	if (write_to_vect(vector, limit->content) == -1)
		return (-1);
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
	char	*str;
	char	*str_with_nl;

	str = readline("> ");
	while (str && ft_strcmp(str, limit))
	{
		str_with_nl = ft_strjoin(str, "\n");
		free(str);
		if (str_with_nl == NULL)
			return (-1);
		if (add_vector(vect, str_with_nl, ft_strlen(str_with_nl)) == -1)
		{
			free(str_with_nl);
			return (-1);
		}
		free(str_with_nl);
		str = readline("> ");
	}
	if (str)
		free(str);
	return ((errno == 0) - 1);
}
