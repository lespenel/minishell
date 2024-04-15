/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refill_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 01:04:22 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/15 01:17:44 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "signals.h"
#include "ft_string.h"
#include "lexer.h"
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

static char	*get_new_s(char *input, char *s, ssize_t len);
static char	*readline_sig(void);
static int	remove_nl(t_vector *new_s);

ssize_t	refill_lexer(t_lexer *lexer, char *s)
{
	const ssize_t	len = ft_strlen(s);
	char			*input;
	char			*new_s;

	input = readline_sig();
	if (errno)
		return (-1);
	if (g_sig == SIGINT)
		return (0);
	if (input == NULL)
	{
		ft_dprintf(2, UNEXPECTED_EOF);
		return (1);
	}
	new_s = get_new_s(input, s, len);
	free(input);
	if (new_s == NULL)
		return (-1);
	if (fill_lexer(lexer, new_s) == -1)
	{
		free(new_s);
		return (-1);
	}
	free(new_s);
	return (0);
}

static char	*readline_sig(void)
{
	char	*input;

	input = readline("> ");
	if (g_sig == SIGINT)
	{
		if (input)
			free(input);
		return (NULL);
	}
	return (input);
}

static int	remove_nl(t_vector *new_s)
{
	size_t	i;
	char	*s;
	char	quote;

	i = 0;
	s = new_s->array;
	quote = 0;
	while (s[i])
	{
		if (is_quote(s[i]) && quote == 0)
			quote = s[i];
		else if (s[i] == quote)
			quote = 0;
		if ((s[i] == '\\' && quote == '\'' && s[i + 1])
			|| (s[i] == '\\' && s[i + 1] && s[i + 1] != '\n'))
			++i;
		else if (ft_strncmp(s + i, "\\\n", 2) == 0)
		{
			remove_vector(new_s, i);
			remove_vector(new_s, i);
			--i;
		}
		++i;
	}
	return (0);
}

static	char	*get_new_s(char *input, char *s, ssize_t len)
{
	t_vector	new_s;

	init_vector(&new_s, sizeof(char));
	if (add_vector(&new_s, s, len) == -1
		|| add_vector(&new_s, "\n", 1) == -1
		|| add_vector(&new_s, input, ft_strlen(input)) == -1)
	{
		clear_vector(&new_s);
		return (NULL);
	}
	remove_nl(&new_s);
	return (new_s.array);
}
