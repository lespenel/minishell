/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 23:56:24 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/01 07:18:15 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "vector.h"

typedef enum e_lex_type
{
	WORD,
	WORD_SQUOTED,
	WORD_DQUOTED,
	OPERAND, //‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’. 
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HERE_DOC,
}	t_lex_type;

typedef struct s_lexer_tok
{
	char		*content;
	t_lex_type	type;
}	t_lexer_tok;

typedef t_vector	t_lexer;

void	init_lexer(t_lexer *lexer);
int		clear_lexer(t_lexer *lexer);
int		fill_lexer(t_lexer *lexer, char *s);
int		check_lexer(t_lexer *lexer);
int		print_lexer(t_lexer *lexer);

int		is_operand(char c);
int		is_blank(char c);
int		to_next_quote(char *str);
int		is_word(char c);
int		is_quote(char c);

#endif
