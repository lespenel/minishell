/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_stds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:04:33 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/16 14:04:00 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	save_stds(int fd[2])
{
	fd[STDIN_FILENO] = dup(STDIN_FILENO);
	if (fd[STDIN_FILENO] == -1)
		return (-1);
	fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (fd[STDOUT_FILENO] == -1)
	{
		close(fd[STDIN_FILENO]);
		return (-1);
	}
	return (0);
}
