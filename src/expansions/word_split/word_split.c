/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:30:17 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/28 04:52:42 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"

// needs to be done
int	word_split(t_lexer_tok *token)
{
	size_t			i;
	t_vector		newtab;

	i = 0;
	while (i < token->args.size)
	{
		init_vector(&newtab, sizeof(char *));
		++i;
	}
	i = 0;
	while (i < token->redirections.size)
	{
		++i;
	}
	return (0);
}
