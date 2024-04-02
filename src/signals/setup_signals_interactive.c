/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals_interactive.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:01:57 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/02 13:09:52 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>

static void	interactive_sigint(int sig);
static void	interactive_sigquit(int sig);

void	setup_signals_interactive(void)
{
	signal(SIGINT, interactive_sigint);
	signal(SIGQUIT, interactive_sigquit);
}

static void	interactive_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	interactive_sigquit(int sig)
{
	(void)sig;
}
