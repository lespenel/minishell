/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:50:20 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/17 02:01:37 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"
#include <unistd.h>

int	ms_pwd(t_env *env, char **args)
{
	int		argc;
	char	*wd;

	argc = 0;
	while (args[argc])
		argc++;
	wd = ms_getenv(env, "PWD");
	if (wd == NULL)
		return (-1);
	if (write(1, wd, ft_strlen(wd)) == -1)
		return (-1);
	if (write(1, "\n", 1) == -1)
		return (-1);
	return (0);
}
