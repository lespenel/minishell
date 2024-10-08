/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:52:19 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/15 04:48:01 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# define EXPORT_ID "minishell: export: `%s': not a valid identifier\n"
# define UNSET_ID "minishell: unset: `%s': not a valid identifier\n"
# define SHLVL_TOO_HIGH "minishell: warning: shell level (%s) too high,\
 resetting to 1\n"

# include "hashmap.h"

typedef t_hashmap	t_env;

int		init_env(t_env *env, char *envp[]);
void	destroy_env(t_env *env);
int		print_env(t_env *env);
int		ms_setenv(t_env *env, char *key, char *value);
char	*ms_getenv(t_env *env, char *key);
char	*ms_getnenv(t_env *env, char *key, size_t n);
void	ms_unsetenv(t_env *env, const char *key);
char	*ms_get_path(t_env *env, char *file);
char	**get_envp(t_env *env);
int		is_valid_identifier(char *str);

#endif
