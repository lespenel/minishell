/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_stds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:06:00 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/03 13:14:10 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	restore_stds(int fd[2])
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (close(fd[0]) == -1)
	{
		close(fd[1]);
		return (-1);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		return (-1);
	}
	if (close(fd[1]) == -1)
		return (-1);
	return (0);
}
