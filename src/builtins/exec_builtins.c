/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:11:40 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/18 03:20:34 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "builtins.h"

int	exec_builtins(t_minishell *minishell, t_lexer *lexer, char **args)
{
	const t_buitlins_map	builtins_map[] = {{"echo", ms_echo},
	{"cd", ms_cd}, {"pwd", ms_pwd}, {"export", ms_export},
	{"unset", ms_unset}, {"env", ms_env}};
	int						i;

	i = 0;
	while (i < EXIT)
	{
		if (ft_strcmp(builtins_map[i].name, args[0]) == 0)
			return (builtins_map[i].func(&minishell->env, args));
		++i;
	}
	if (ft_strcmp("exit", args[0]) == 0)
		return (ms_exit(minishell, lexer, args));
	return (0);
}
