/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parameter_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:06:42 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/06 23:09:41 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"
#include "minishell.h"

char	*get_parameter_str(t_ms *ms, char *s, size_t n)
{
	if (ft_strncmp(s, "?", n) == 0)
		return (ms->lastexitstr);
	return (ms_getnenv(&ms->env, s, n));
}
