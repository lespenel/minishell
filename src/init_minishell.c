/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 02:39:38 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 02:40:02 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include "env.h"
#include "minishell.h"
#include "signals.h"
#include "util.h"

int	init_minishell(t_ms *ms, char *envp[])
{
	ft_memset(ms, 0, sizeof(t_ms));
	if (setup_termios(ms) == -1)
		return (-1);
	if (init_env(&ms->env, envp) == -1)
		return (-1);
	init_hashmap(&ms->aliases);
	setup_signals_interactive();
	ms->signaled = 0;
	if (set_exitcode_str(ms, 0) == -1)
		return (-1);
	(void)ms;
	(void)envp;
	return (0);
}
