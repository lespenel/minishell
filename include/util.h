/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:46:36 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/09 07:22:54 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "env.h"
# include "minishell.h"
# include <stddef.h>

char	*ms_strchr(char *str, char c);
size_t	next_char(char *s, size_t i);
char	*get_ifs(t_env *env);
void	clear_string_vector(t_vector *this);
int		dup_and_close(int fd1, int fd2);
int		set_exitcode_str(t_ms *ms, int exitcode);
pid_t	ms_fork(void);

#endif
