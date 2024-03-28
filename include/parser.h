/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:44:01 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/28 11:54:48 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

int	validate_input(t_lexer *lexer);
int	get_here_doc(t_lexer *lexer);
int	fill_here_doc(t_vector *vector, char *path, char *limiter);

#endif
