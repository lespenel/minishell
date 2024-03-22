/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 23:56:24 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/22 01:47:25 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "vector.h"

# define SYNTAX_ERR "minishell: syntax error near unexpected token `%s'\n"

typedef enum e_lex_type
{
	LOGICAL_OR,
	LOGICAL_AND,
	APPEND,
	HERE_DOC,
	PIPE,
	OPEN_BRACE,
	CLOSE_BRACE,
	REDIRECT_IN,
	REDIRECT_OUT,
	NEWLINE,
	WORD,
	SUBSHELL
}	t_lex_type;

typedef t_vector	t_lexer;

typedef struct s_lexer_tok
{
	t_lex_type	type;
	char		*content;
	t_lexer		subshell;
}	t_lexer_tok;


void	init_lexer(t_lexer *lexer);
int		clear_lexer(t_lexer *lexer);
int		fill_lexer(t_lexer *lexer, char *s);
int		add_newline_tok(t_lexer *lexer);
int		print_lexer(t_lexer *lexer);

int		is_operand(char c);
int		is_blank(char c);
size_t	to_next_quote(char *s);
int		is_word(char c);
int		is_quote(char c);

#endif
