/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:27:04 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/20 02:46:53 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "minishell.h"
# include <stdio.h>

int		expand_tokens(t_ms *minishell, t_lexer *lexer);
ssize_t	expand_substr(t_ms *minishell, t_lexer *lexer, t_vector *new, char *s);
int		add_escaping(t_vector *vector, char *s);
ssize_t	treat_noquote(t_ms *ms, t_lexer *lex, t_vector *new, char *s);

#endif
