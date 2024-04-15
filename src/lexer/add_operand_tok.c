/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_operand_tok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:09:47 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/10 07:15:46 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"

static int	get_operand_token(const char *operand_type[], char *s);

int	add_operand_tok(t_lexer *lexer, char *s)
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
	t_lexer_tok			token;
	int					type;

	type = get_operand_token(operand_type, s);
	if (type == -1)
		return (0);
	token.content = NULL;
	token.type = type;
	if (add_vector(lexer, &token, 1) == -1)
		return (-1);
	return (ft_strlen(operand_type[type]));
}

static int	get_operand_token(const char *operand_type[], char *s)
{
	size_t	i;

	i = 0;
	while (i <= REDIRECT_OUT)
	{
		if (ft_strncmp(operand_type[i], s, ft_strlen(operand_type[i])) == 0)
			return (i);
		++i;
	}
	return (-1);
}
