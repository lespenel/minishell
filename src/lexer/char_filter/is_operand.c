/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:13:36 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/21 07:33:30 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "chargroups.h"
#include "lexer.h"

inline int	is_operand(char c)
{
	return (ft_strchr(METACHAR, c) != NULL);
}
