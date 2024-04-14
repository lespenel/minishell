/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:27:04 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/12 06:16:27 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "minishell.h"
# include "vector.h"
# include <stdio.h>

int		expand_parameters(t_ms *ms, t_lexer_tok *token);
int		expand_wildcards(t_env *env, t_lexer_tok *token);
ssize_t	expand_substring(t_ms *ms, t_vector *news, char *s, t_vector *tab);
int		add_escaping(t_vector *vector, char *s);
ssize_t	treat_noquote(t_ms *ms, t_vector *new, char *s, t_vector *tab);
int		perform_expansions(t_ms *ms, t_lexer_tok *token);
int		word_split(t_ms *ms, t_lexer_tok *token);
int		quote_removal(t_lexer_tok *token);
int		tilde_expansion(t_ms *ms, t_lexer_tok *token);
ssize_t	expand_nq(t_ms *ms, t_vector *tab, t_vector *new, char *value);
char	*ft_strtok_ifs(char *s, const char *delim);
int		add_word_tab(t_vector *tab, t_vector *word);
int		fill_nq_var(t_vector *tab, t_vector *new, char *value, const char *ifs);
char	*get_parameter_str(t_ms *ms, char *s, size_t n);
int		remove_quotes(char **s);

#endif
