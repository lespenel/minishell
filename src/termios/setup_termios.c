/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_termios.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 05:08:42 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/14 18:27:42 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <unistd.h>

int	setup_termios(t_ms *ms)
{
	const int	fd = get_tty_fd();

	if (fd == -1)
		return (0);
	if (tcgetattr(fd, &ms->oldtermios) == -1)
		return (-1);
	ms->termios = ms->oldtermios;
	ms->termios.c_cc[VQUIT] = 0;
	if (tcsetattr(fd, TCSANOW, &ms->termios) == -1)
		return (-1);
	return (0);
}
