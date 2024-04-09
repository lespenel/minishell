/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_stds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:04:33 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/03 13:05:34 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	save_stds(int fd[2])
{
	fd[0] = dup(STDIN_FILENO);
	if (fd[0] == -1)
		return (-1);
	fd[1] = dup(STDIN_FILENO);
	if (fd[1] == -1)
	{
		close(fd[0]);
		return (-1);
	}
	return (0);
}
