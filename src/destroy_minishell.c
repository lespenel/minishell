/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:52:42 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/08 05:15:33 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	destroy_minishell(t_ms *ms)
{
	restore_termios(ms);
	destroy_env(&ms->env);
	if (ms->lastexitstr)
	{
		free(ms->lastexitstr);
		ms->lastexitstr = NULL;
	}
}
