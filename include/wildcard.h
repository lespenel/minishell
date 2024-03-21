/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/21 11:27:00 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "env.h"
# include "lexer.h"

int		add_match_tok(t_lexer *matches, char *s);
int		expand_wildcards(t_env *env, t_lexer *lexer);
int		fill_pattern(t_lexer *pattern, char *raw_pattern);
int		get_matching_filenames(t_env *env, t_lexer *fnames, t_lexer_tok *tok);
int		is_wildcard_match(t_lexer *pattern, char *raw_pattern, char *f_name);
int		remove_backslash(t_lexer *pattern);
void	sort_filenames(t_lexer *filenames);

#endif
