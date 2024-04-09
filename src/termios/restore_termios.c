/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_termios.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 05:12:32 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/09 04:13:25 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <unistd.h>

int	restore_termios(t_ms *ms)
{
	const int	fd = get_tty_fd();

	if (fd == -1)
		return (0);
	if (tcsetattr(fd, TCSANOW, &ms->oldtermios) == -1)
		return (-1);
	return (0);
}
