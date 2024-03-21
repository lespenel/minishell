/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_blank.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:12:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/21 07:33:40 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "chargroups.h"
#include "lexer.h"

inline int	is_blank(char c)
{
	return (ft_strchr(DEFAULT_IFS, c) != NULL);
}
