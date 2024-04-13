/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals_interactive.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:01:57 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/13 17:22:20 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>

static void	interactive_sigint(int sig);
static void	interactive_sigquit(int sig);
static int	event(void);

void	setup_signals_interactive(void)
{
	rl_event_hook = event;
	signal(SIGINT, interactive_sigint);
	signal(SIGQUIT, interactive_sigquit);
}

static void	interactive_sigint(int sig)
{
	g_sig = sig;
	rl_done = 1;
}

static void	interactive_sigquit(int sig)
{
	(void)sig;
}

static int	event(void)
{
	return (0);
}
