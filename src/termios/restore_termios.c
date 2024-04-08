/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_termios.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 05:12:32 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/08 05:13:26 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <unistd.h>

int	restore_termios(t_ms *ms)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &ms->oldtermios) == -1)
		return (-1);
	return (0);
}
