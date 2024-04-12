/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tempfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:50:51 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/12 10:23:45 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "parser.h"
#include "ft_math.h"
#include <ft_util.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

static int	open_urandom(char *path);
static int	fill_random_alpha(int fd, char *path);

int	get_tempfile(char *path)
{
	int	fd;

	ft_strncpy(path, "/tmp/minishell-thd.000000", 26);
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

	buff[1] = '\0';
	i = 0;
	while (i < 6 && fd)
	{
		if (read(fd, buff, 1) == -1)
			return (-1);
		path[19 + i] = ALNUM[ft_abs(buff[0] % 62)];
		++i;
	}
	return (0);
}
