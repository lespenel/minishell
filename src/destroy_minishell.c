/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:52:42 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/14 23:10:45 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	destroy_minishell(t_ms *ms)
{
	restore_termios(ms);
	destroy_env(&ms->env);
	destroy_env(&ms->aliases);
	if (ms->lastexitstr)
	{
		free(ms->lastexitstr);
		ms->lastexitstr = NULL;
	}
}
