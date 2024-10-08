/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:54:45 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/16 15:25:03 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtins.h"
#include "expander.h"
#include "lexer.h"
#include "execution.h"
#include "ft_string.h"
#include "signals.h"
#include "vector.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	run_builtin(t_ms *ms, t_lexer *lexer, size_t i)
{
	t_lexer_tok	*token;
	int			ret;
	int			stds[2];

	token = at_vector(lexer, i);
	if (save_stds(stds) == -1)
		return (-1);
	ret = perform_redirections(token);
	if (ret == -1)
	{
		restore_stds(stds);
		return (-1);
	}
	if (ret == 1)
	{
		if (restore_stds(stds) == -1)
			return (-1);
		return (1);
	}
	ret = exec_builtins(ms, lexer, i);
	if (restore_stds(stds) == -1)
		return (-1);
	if (g_sig == SIGINT)
		return (128 + SIGINT);
	return (ret);
}
