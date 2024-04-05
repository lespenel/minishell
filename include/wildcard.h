/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/05 01:48:06 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "env.h"
# include "lexer.h"
# include "vector.h"
# include <dirent.h>
# include <sys/types.h>

typedef enum e_pattern_type
{
	FILENAME,
	DIRECTORY,
	NO_STAR,
}	t_pattern_type;

typedef struct s_pattern
{
	t_lexer			pattern;
	t_pattern_type	type;
}	t_pattern;

typedef struct s_wildcard
{
	t_vector	patterns;
	t_vector	glob_patterns;
	size_t		nb_dir;
	char		*wd;
	int			absolute_path;
	size_t		wd_size;
	char		*globignore;
	t_vector	*f_lst_ptr;
}	t_wild;

int		expand_wildcards(t_env *env, t_lexer_tok *token);
int		wildcard_handling(t_env *env, t_vector *filenames, char *raw_pattern);
int		create_pattern(t_wild *wildcard, char *raw_pattern);
int		create_dir_pattern(t_wild *wildcard, t_lexer *first_pattern, int i);
int		create_file_pattern(t_wild *wildcard, t_lexer *first_pattern, int i);
int		create_glob_pattern(t_wild *wild);
int		fill_pattern(t_lexer *pattern, char *raw_pattern);
int		compare_pattern(t_wild *wildcard, t_vector *filenames);
int		compare_globignore(t_wild *wild, char *f_name);
DIR		*get_dir_path(t_wild *wild, char *path);
int		get_dir_ls(t_wild *w, t_lexer *pattern, t_vector *fnames, char *path);
int		get_files_ls(t_wild *w, t_lexer *pattern, t_vector *fname, char *path);
int		add_file_tok(t_lexer *filenames, char *s);
int		add_match_tok(t_lexer *matches, char *s);
int		is_wildcard_match(t_wild *wild, t_lexer *pattern, char *f_name);
int		get_matching_dirname(t_wild *wild, t_vector *filenames, size_t nb_dir);
int		get_matching_filenames(t_wild *wildcard, t_vector *filenames);
int		remove_backslash(t_lexer *pattern);
int		add_backslash(t_vector *filenames);
void	sort_filenames(t_vector *filenames, ssize_t start, ssize_t end);

#endif
