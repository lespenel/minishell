/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:19:20 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 02:45:22 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "env.h"
# include "lexer.h"
# include <termios.h>

typedef struct s_ms
{
	t_env			env;
	t_env			aliases;
	int				signaled;
	int				lastexit;
	char			*lastexitstr;
	struct termios	oldtermios;
	struct termios	termios;
}	t_ms;

int		setup_termios(t_ms *ms);
int		restore_termios(t_ms *ms);
int		get_tty_fd(void);
void	destroy_minishell(t_ms *ms);
int		parse_input(t_ms *ms, t_lexer *lexer, char *input);
int		init_minishell(t_ms *ms, char *envp[]);
int		run_shell(t_ms *ms);

#endif
