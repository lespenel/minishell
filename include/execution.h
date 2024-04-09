/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 01:40:39 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/09 06:08:40 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "lexer.h"
# include <sys/wait.h>

int			run_command(t_ms *ms, t_lexer *lexer, size_t i);
int			run_builtin(t_ms *ms, t_lexer_tok *token);
int			execute_commands(t_ms *ms, t_lexer *lexer);
int			execute_simple_command(t_ms *ms, t_lexer *lexer, size_t i);
int			execute_pipeline(t_ms *ms, t_lexer *lexer, size_t i);
int			execute_subshell(t_ms *ms, t_lexer *lexer, size_t i);
int			perform_redirections(t_lexer_tok *token);
int			execution_structure(t_lexer *lexer);
int			simplify_tokens(t_lexer *lexer);
char		*get_path(t_ms *ms, char *name);
t_lex_type	next_token(t_lexer *lexer, size_t i);
int			wait_children(pid_t last);
int			save_stds(int fd[2]);
int			restore_stds(int fd[2]);
int			execute_pipe_cmd(t_ms *ms, t_lexer *lexer, size_t i, int fdin);
int			exec_cmd(t_ms *ms, t_lexer_tok *token, char *path);

#endif
