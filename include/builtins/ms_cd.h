/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 00:22:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/10 00:31:33 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_CD_H
# define MS_CD_H

# include "env.h"

# define NO_SUCH_FILE "minishell: cd: %s: No such file or directory\n"
# define FILENAME_TO_LONG "minishell: cd: %s: File name too long\n"
# define HOME_NOT_SET "minishell: cd: HOME not set\n"
# define OLDPWD_NOT_SET "minishell: cd: OLDPWD not set\n"
# define TOO_MANY_ARGS "minishell: cd: too many arguments\n"

char	*get_wd(t_env *env);
char	*get_curpath(t_env *env, char *dir_operand);
char	*compare_cdpath(t_env *env, char *dir_operand);
char	*get_dir_operand(t_env *env, char **args);
int		check_path_size(t_env *env, char **curpath, char *dir_operand);
int		get_canonical_path(t_env *env, char **curpath, char *dir_operand);
int		remove_dot_dot(t_env *env, t_vector *npath, t_vector *s_path, char *op);
int		change_directory(t_env *env, char **curpath, char *dir_operand);

#endif
