/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/24 16:26:18 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "env.h"
# include "lexer.h"

typedef enum e_pattern_type
{
	FILENAME,
	DIRECTORY,
} t_pattern_type;

typedef struct	s_pattern
{
	t_lexer	 		pattern;
	t_pattern_type	type;
}	t_pattern;

typedef struct s_wildcard
{
	t_vector patterns;
	int		 nb_dir;
	char 	 *start_with;
	char	 *end_with;
	t_lexer	 file_list;
}	t_wildcard;

int	add_dir_tok(t_lexer *filenames, char *s, int directory);

int		get_dir_ls(t_lexer *filenames, char *path);
int		expand_wildcards(t_env *env, t_lexer *lexer);
int		create_pattern(t_wildcard *wildcard, char *raw_pattern);
int		create_dir_pattern(t_wildcard *wildcard, t_lexer *first_pattern, int i);
int		fill_pattern(t_lexer *pattern, char *raw_pattern);
int		add_file_pattern(t_wildcard *wildcard, t_lexer *first_pattern, int i);
int		wildcard_handling(t_lexer *filenames, char *raw_pattern);
int		is_wildcard_match(t_lexer *pattern, char *f_name);
int		get_matching_dirname(t_wildcard *wildcard, t_lexer *filenames, int nb_dir);
int	get_matching_filenames(t_wildcard *wildcard, t_lexer *filenames);
int		compare_pattern(t_wildcard *wildcard, t_lexer *filenames);
int		get_files_ls(t_lexer *filenames, char *to_find);

int		add_match_tok(t_lexer *matches, char *s);
//int		get_matching_filenames(t_env *env, t_lexer *fnames, t_lexer_tok *tok);
//int		is_wildcard_match(t_lexer *pattern, char *raw_pattern, char *f_name);
int		remove_backslash(t_lexer *pattern);
void	sort_filenames(t_lexer *filenames);

#endif
