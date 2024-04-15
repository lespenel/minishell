/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 04:10:46 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/14 23:13:58 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_io.h"
#include "env.h"
#include "minishell.h"

int	ms_unalias(t_ms *ms, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]) == 0 || ft_strchr(args[i], '='))
		{
			ft_dprintf(2, UNSET_ID, args[i]);
			return (1);
		}
		ms_unsetenv(&ms->aliases, args[i]);
		++i;
	}
	return (0);
}
