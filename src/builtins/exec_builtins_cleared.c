/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins_cleared.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:17:46 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/16 15:18:42 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "builtins.h"
#include "lexer.h"
#include "vector.h"

int	exec_builtins_cleared(t_ms *minishell, t_lexer_tok *token)
{
	const t_buitlins_map	builtins_map[] = {{"alias", ms_alias},
	{"echo", ms_echo}, {"cd", ms_cd}, {"pwd", ms_pwd},
	{"export", ms_export}, {"unalias", ms_unalias},
	{"unset", ms_unset}, {"env", ms_env}};
	int						j;
	char					**args;

	args = token->args.array;
	j = 0;
	while (j < MS_EXIT)
	{
		if (ft_strcmp(builtins_map[j].name, args[0]) == 0)
			return (builtins_map[j].func(minishell, args));
		++j;
	}
	if (ft_strcmp("exit", args[0]) == 0)
		return (ms_exit(minishell, token, args));
	return (0);
}
