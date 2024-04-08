/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:19:20 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/08 05:45:13 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell $> "

# include "env.h"
# include "lexer.h"
# include <termios.h>

typedef struct s_ms
{
	t_env			env;
	int				signaled;
	int				lastexit;
	char			*lastexitstr;
	struct termios	oldtermios;
	struct termios	termios;
}	t_ms;

int		setup_termios(t_ms *ms);
int		restore_termios(t_ms *ms);
void	destroy_minishell(t_ms *ms);
int		parse_input(t_ms *ms, t_lexer *lexer, char *input);

#endif
