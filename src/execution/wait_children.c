/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:56:22 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/07 08:23:07 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

int	wait_children(t_ms *ms, pid_t last)
{
	int		wstatus;
	pid_t	pid;
	int		ret;

	pid = 0;
	ret = -1;
	while (pid != -1)
	{
		pid = wait(&wstatus);
		if (pid == last)
		{
			ms->signaled = WIFSIGNALED(wstatus);
			if (WIFEXITED(wstatus))
				ret = WEXITSTATUS(wstatus);
			if (WIFSIGNALED(wstatus))
				ret = 128 + WTERMSIG(wstatus);
		}
	}
	if (errno != ECHILD)
		return (-1);
	return (ret);
}
