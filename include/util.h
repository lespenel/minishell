/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:46:36 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/21 07:40:41 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "minishell.h"
# include <stddef.h>

char	*get_ifs(t_ms *ms);
size_t	next_char(char *s, size_t i);

#endif
