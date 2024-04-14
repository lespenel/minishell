/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:44:01 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/14 17:02:08 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define ALNUM "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
# define HERE_DOC_EOF "minishell: warning: here-document \
delimited by end-of-file (wanted `%s')\n"

# include "vector.h"
# include "lexer.h"
# include "minishell.h"

int	validate_input(t_ms *ms, t_lexer *lexer);
int	syntax_error(int type);
int	get_here_doc(t_ms *ms, t_lexer *lexer);
int	add_here_doc_str(t_ms *ms, t_vector *vect, char *s);
int	fill_here_doc(t_ms *ms, t_vector *vector, char *path, t_lexer_tok *limit);
int	get_tempfile(char *path);

#endif
