/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:56:53 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/03 03:32:18 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "lexer.h"

int	syntax_error(int type)
{
	static const char	*operand_type[] = {
	[LOGICAL_OR] = "||",
	[LOGICAL_AND] = "&&",
	[APPEND] = ">>",
	[HERE_DOC] = "<<",
	[PIPE] = "|",
	[OPEN_BRACE] = "(",
	[CLOSE_BRACE] = ")",
	[REDIRECT_IN] = "<",
	[REDIRECT_OUT] = ">",
	};

	if (ft_dprintf(2, SYNTAX_ERR, operand_type[type]) == -1)
		return (-1);
	return (1);
}
