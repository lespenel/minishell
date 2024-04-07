/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:46:36 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/07 05:01:31 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stddef.h>
# include "env.h"

char	*ms_strchr(char *str, char c);
size_t	next_char(char *s, size_t i);
char	*get_ifs(t_env *env);
int		dup_and_close(int fd1, int fd2);
int		set_exitcode_str(t_ms *ms, int exitcode);

#endif
