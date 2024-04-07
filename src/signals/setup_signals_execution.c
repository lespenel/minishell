/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:01:57 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/07 08:24:41 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <signal.h>
#include <unistd.h>

static void	execution_sigint(int sig);
static void	execution_sigquit(int sig);

void	setup_signals_execution(void)
{
	signal(SIGINT, execution_sigint);
	signal(SIGQUIT, execution_sigquit);
}

static void	execution_sigint(int sig)
{
	(void)sig;
}

static void	execution_sigquit(int sig)
{
	(void)sig;
}
