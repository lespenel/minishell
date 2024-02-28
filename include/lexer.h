/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 23:56:24 by lespenel          #+#    #+#             */
/*   Updated: 2024/02/28 01:12:16 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "vector.h"

typedef enum e_lex_type
{
	CMD,
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

void	init_lexer(t_lexer *token_tab);
int		fill_lexer(t_lexer *token_tab, t_lexer_tok *token);
int		check_lexer(t_lexer *token_tab);
int		destroy_lexer(t_lexer *token_tab);
int		print_lexer(t_lexer *token_tab);

#endif
