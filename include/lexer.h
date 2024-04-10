/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 23:56:24 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/10 08:24:22 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "vector.h"
# include <sys/types.h>

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
	COMMAND,
	SUBSHELL
}	t_lex_type;

typedef t_vector	t_lexer;

typedef struct s_redirection
{
	t_lex_type	type;
	char		*file;
	t_vector	newtab;
	int			fd;
}	t_redirection;

typedef struct s_lexer_tok
{
	t_lex_type	type;
	char		*content;
	t_lexer		subshell;
	t_vector	args;
	t_vector	redirections;
}	t_lexer_tok;

void	init_lexer(t_lexer *lexer);
void	clear_token(t_lexer_tok *token);
int		clear_lexer(t_lexer *lexer);
void	clear_lexer_except(t_lexer *lexer, size_t i, t_lexer_tok *token);
int		fill_lexer(t_lexer *lexer, char *s);
ssize_t	add_word_tok(t_lexer *lexer, char *s);
int		add_operand_tok(t_lexer *lexer, char *s);
int		add_newline_tok(t_lexer *lexer);
int		print_lexer(t_lexer *lexer);
int		is_operand(char c);
int		is_blank(char c);
size_t	to_next_quote(char *s);
int		is_word(char *s);
int		is_quote(char c);

#endif
