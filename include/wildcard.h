/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/13 06:21:29 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "env.h"
# include "lexer.h"

int	expand_wildcards(t_env *env, t_lexer *lexer);
int	get_matching_filenames(t_env *env, t_lexer *filenames, t_lexer_tok *token);
int	fill_pattern(t_lexer *pattern, char *raw_pattern);
int	is_wildcard_match(char	*motif, char *f_name);

#endif
