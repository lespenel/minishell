/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:27:04 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/03 11:37:05 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "minishell.h"
# include <stdio.h>

int		expand_parameters(t_ms *minishell, t_lexer_tok *token);
ssize_t	expand_substr(t_ms *minishell, t_vector *new, char *s);
int		add_escaping(t_vector *vector, char *s);
ssize_t	treat_noquote(t_ms *ms, t_vector *new, char *s);
int		perform_expansions(t_ms *ms, t_lexer_tok *token);
int		word_split(t_ms *ms, t_lexer_tok *token);
int		quote_removal(t_lexer_tok *token);
int		tilde_expansion(t_ms *ms, t_lexer_tok *token);

#endif
