/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tty_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 04:09:50 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/09 04:19:11 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	get_tty_fd(void)
{
	if (isatty(STDERR_FILENO))
		return (STDERR_FILENO);
	if (isatty(STDOUT_FILENO))
		return (STDOUT_FILENO);
	if (isatty(STDIN_FILENO))
		return (STDIN_FILENO);
	return (-1);
}
