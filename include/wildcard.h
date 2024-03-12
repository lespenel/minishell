/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/12 09:11:47 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "env.h"
# include "lexer.h"

int	fill_pattern(t_lexer *pattern, char *raw_pattern);
int	add_lexer_at(t_lexer *lexer, t_lexer *new_lex, size_t index);
int	expand_wildcard(t_env *env, t_lexer *lexer);
int	is_wildcard_match(char	*motif, char *f_name);
int	get_files_ls(t_env *env, t_lexer *matches);

#endif
