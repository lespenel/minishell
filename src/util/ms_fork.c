/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:48:49 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/04 14:45:17 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <unistd.h>

pid_t	ms_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		setup_signals_child();
	return (pid);
}
