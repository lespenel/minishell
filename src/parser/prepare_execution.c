/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:01:01 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/01 07:07:18 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include "ft_string.h"
#include "ft_mem.h"

static int	replace_env(t_lexer_tok *token, char *envp[]);
static int	replace_singular(t_lexer_tok *token, char *dollarptr, size_t len);

int	prepare_execution(t_lexer *lexer, char *envp[])
{
	size_t		i;
	t_lexer_tok	*token;

	i = 0;
	while (i < lexer->size)
	{
		token = at_vector(lexer, i);
		if (token->type == WORD)
			replace_env(token, envp);
	}
	return (0);
}

static int	replace_env(t_lexer_tok *token, char *envp[])
{
	size_t	i;
	char	*dollarptr;

	(void)envp;
	dollarptr = ft_strchr(token->content, '$');
	while (dollarptr)
	{
		i = 1;
		while (dollarptr[i] && dollarptr[i] != ' ' && dollarptr[i] != '\t' && dollarptr[i] != '$')
			++i;
		if (i == 1)
			dollarptr = ft_strchr(dollarptr + 1, '$');
		else
		{
			replace_singular(token, dollarptr, i);
			dollarptr = ft_strchr(token->content, '$');
		}
	}
	return (0);
}

// TODO: think about how to handle env variables
static int	replace_singular(t_lexer_tok *token, char *dollarptr, size_t len)
{
	const char	c = dollarptr[len];
	char		*env;
	size_t		envlen;
	size_t		alloc;
	char		*s;

	dollarptr[len] = '\0';
	env = getenv(dollarptr + 1);
	if (env == NULL)
		env = "";
	envlen = ft_strlen(env);
	dollarptr[len] = c;
	alloc = (ft_strlen(token->content) + envlen + 1) - len;
	s = malloc(alloc * sizeof(char));
	ft_memcpy(s, token->content, dollarptr - token->content);
	ft_memcpy(s + (dollarptr - token->content), env, envlen);
	ft_memcpy(s + (dollarptr - token->content) + envlen, dollarptr + len, (token->content + ft_strlen(token->content)) - dollarptr - len);
	s[envlen + ft_strlen(token->content) - len] = '\0';
	free(token->content);
	token->content = s;
	return (0);
}
