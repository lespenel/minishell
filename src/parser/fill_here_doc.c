/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 19:57:58 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/28 16:22:35 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_math.h"
#include "ft_string.h"
#include "parser.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static int	open_urandom(char *path);
static int	fill_random_alpha(int fd, char *path);
static int	get_tempfile(char *path);
static int	write_data_to_vect(t_vector *vect, char *limiter);

int	fill_here_doc(t_vector *vector, char *path, char *limiter)
{
	int			fd;

	if (write_data_to_vect(vector, limiter) == -1)
		return (-1);
	fd = get_tempfile(path);
	if (fd == -1)
		return (-1);
	if (write(fd, vector->array, vector->size) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	write_data_to_vect(t_vector *vect, char *limiter)
{
	char		*str;
	char		*str_with_nl;

	str = readline("> ");
	while (str && ft_strcmp(str, limiter))
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

static int	get_tempfile(char *path)
{
	int	fd;

	ft_strlcpy(path, "/tmp/minishell-thd.000000", 26);
	if (open_urandom(path) == -1)
		return (-1);
	errno = 0;
	fd = open(path, O_CREAT | O_RDWR | O_EXCL, 0600);
	if (fd == -1)
		return (-1);
	return (fd);
}

static int	open_urandom(char *path)
{
	int		fd;
	int		i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (-1);
	if (fill_random_alpha(fd, path) == -1)
	{
		close(fd);
		return (-1);
	}
	i = 0;
	while (access(path, F_OK) == 0 && i < 1000)
	{
		if (fill_random_alpha(fd, path) == -1)
		{
			close(fd);
			return (-1);
		}
		++i;
	}
	close(fd);
	if (i == 1000)
		return (-1);
	return (0);
}

static int	fill_random_alpha(int fd, char *path)
{
	int8_t		i;
	char		buff[2];
	const char	alnum[62] = "abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"0123456789";

	buff[1] = '\0';
	i = 0;
	while (i < 6 && fd)
	{
		if (read(fd, buff, 1) == -1)
			return (-1);
		path[19 + i] = alnum[ft_abs(buff[0] % 62)];
		++i;
	}
	return (0);
}
