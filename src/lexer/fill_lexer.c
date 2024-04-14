/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/14 18:24:48 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "signals.h"
#include "vector.h"
#include "util.h"
#include "ft_io.h"
#include "parser.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <stdlib.h>

static int		add_tokens(t_lexer *lexer, char *s, size_t i);
static ssize_t	refill_lexer(t_lexer *lexer, char *s);
static char		*get_new_s(char *input, char *s, ssize_t len);
static char		*readline_sig(void);

int	fill_lexer(t_lexer *lexer, char *s)
{
	size_t		i;
	int			ret;

	i = 0;
	ret = 0;
	errno = 0;
	while (s[i])
	{
		ret = add_tokens(lexer, s, i);
		i += ret;
		if (ret == 0)
		{
			clear_lexer(lexer);
			init_lexer(lexer);
			return (refill_lexer(lexer, s));
		}
		else if (ret == -1)
			return (-1);
	}
	add_history(s);
	return (add_newline_tok(lexer));
}

static int	add_tokens(t_lexer *lexer, char *s, size_t i)
{
	int	ret;

	ret = 0;
	if (is_word(s + i))
		ret = add_word_tok(lexer, s + i);
	else if (is_operand(s[i]))
		ret = add_operand_tok(lexer, s + i);
	else
		ret = 1;
	return (ret);
}

static	ssize_t	refill_lexer(t_lexer *lexer, char *s)
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

static	char	*get_new_s(char *input, char *s, ssize_t len)
{
	char	*new_s;

	if (s[len - 1] == '\\')
	{
		s[len - 1] = '\0';
		new_s = ft_strjoin(s, input);
	}
	else
		new_s = ft_strjoin_three(s, "\n", input);
	return (new_s);
}
