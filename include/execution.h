/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 01:40:39 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/25 06:44:02 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "lexer.h"

int		execute_commands(t_ms *ms, t_lexer *lexer);
int		perform_redirections(t_lexer_tok *token);
int		execution_structure(t_lexer *lexer);
int		simplify_tokens(t_lexer *lexer);
char	*get_path(t_ms *ms, char *name);

#endif
