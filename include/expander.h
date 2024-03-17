/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:27:04 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/17 18:59:34 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "minishell.h"
# include <stdio.h>

int		expand_tokens(t_minishell *minishell, t_lexer *lexer);
ssize_t	expand_substring(t_minishell *minishell, t_lexer *lexer, t_vector *new, char *s);

#endif
