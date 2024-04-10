/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 05:26:46 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 11:35:14 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "env.h"
#include <unistd.h>

char	*get_wd(t_env *env)
{
	char	*wd;

	wd = ms_getenv(env, "PWD");
	if (wd != NULL)
		return (ft_strdup(wd));
	wd = getcwd(NULL, 0);
	return (wd);
}
