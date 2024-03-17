/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:48:38 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/17 04:27:28 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

static	int	get_args_len(t_lexer *lexer, size_t index);

char	**get_args(t_lexer *lexer, size_t index)
{
	char		**args;
	size_t		i;
	size_t		args_len;
	t_lexer_tok	*token;

	args_len = get_args_len(lexer, index);
	args = malloc(sizeof(char *) * (args_len + 1));
	if (args == NULL)
		return (NULL);
	i = 0;
	while (i < args_len)
	{
		token = at_vector(lexer, index + i);
		args[i] = ft_strdup(token->content);
		if (args[i] == NULL)
			return (NULL);
		printf("args[%ld] == %s\n", i, args[i]);
		++i;
	}
	args[args_len] = NULL;
	return (args);
}

static	int	get_args_len(t_lexer *lexer, size_t index)
{
	int			argc;
	t_lexer_tok	*token;

	argc = 0;
	token = at_vector(lexer, index);
	while (token->type == WORD)
	{
		++argc;
		token = at_vector(lexer, index + argc);
	}
	return (argc);
}
