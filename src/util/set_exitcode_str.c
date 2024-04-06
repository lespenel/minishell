/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exitcode_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:01:51 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/06 23:03:34 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_string.h"
#include <stdlib.h>

int	set_exitcode_str(t_ms *ms, int exitcode)
{
	ms->lastexit = exitcode;
	if (ms->lastexitstr)
	{
		free(ms->lastexitstr);
		ms->lastexitstr = NULL;
	}
	ms->lastexitstr = ft_itoa(exitcode);
	if (ms->lastexitstr == NULL)
		return (-1);
	return (0);
}
