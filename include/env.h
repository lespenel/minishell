/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:52:19 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/04 08:19:17 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "hashmap.h"

typedef t_hashmap	t_env;

int		init_env(t_env *env, char *envp[]);
int		add_env(t_env *env, char *key, char *value);
void	destroy_env(t_env *env);
void	print_env(t_env *env);

#endif
