/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals_child.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:06:16 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/02 12:50:51 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>

static void	child_sigint(int sig);
static void	child_sigquit(int sig);

void	setup_signals_child(void)
{
	signal(SIGINT, child_sigint);
	signal(SIGQUIT, child_sigquit);

}

static void	child_sigint(int sig)
{
	exit(126 + sig);
}

static void	child_sigquit(int sig)
{
	exit(126 + sig);
}
