/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_termios.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 05:08:42 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/08 05:46:22 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <unistd.h>

int	setup_termios(t_ms *ms)
{
	if (tcgetattr(STDIN_FILENO, &ms->oldtermios) == -1)
		return (-1);
	ms->termios = ms->oldtermios;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &ms->termios) == -1)
		return (-1);
	return (0);
}
