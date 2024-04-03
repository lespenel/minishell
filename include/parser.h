/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:44:01 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/03 03:40:28 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define LOW_ALPHA	"abcdefghijklmnopqrstuvwxyz"
# define UPPER_ALPHA	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define NUM	"0123456789"

# include "lexer.h"

int	validate_input(t_lexer *lexer);
int	syntax_error(int type);
int	get_here_doc(t_lexer *lexer);
int	fill_here_doc(t_vector *vector, char *path, char *limiter);

#endif
