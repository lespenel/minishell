/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ifs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 07:28:44 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/02 03:04:08 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chargroups.h"
#include "hashmap.h"
#include "env.h"

char	*get_ifs(t_env *env)
{
	char	*ifs;

	ifs = getvalue_hashmap(env, "IFS");
	if (ifs == NULL)
		return (DEFAULT_IFS);
	return (ifs);
}
