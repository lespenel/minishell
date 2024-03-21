/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ifs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 07:28:44 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/21 07:38:30 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chargroups.h"
#include "hashmap.h"
#include "minishell.h"

char	*get_ifs(t_ms *ms)
{
	char	*ifs;

	ifs = getvalue_hashmap(&ms->env, "IFS");
	if (ifs == NULL)
		return (DEFAULT_IFS);
	return (ifs);
}
