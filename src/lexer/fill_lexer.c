/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/12 09:27:37 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "lexer.h"
#include "vector.h"
#include "util.h"
#include "ft_io.h"
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <stdlib.h>

static int		add_tokens(t_lexer *lexer, char *s, size_t i);
static ssize_t	refill_lexer(t_lexer *lexer, char *s);
static int		quote_error(char *s);

int	fill_lexer(t_lexer *lexer, char *s)
{
	size_t		i;
	int			ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		ret = add_tokens(lexer, s, i);
		i += ret;
		if (ret == 0)
		{
			ret = refill_lexer(lexer, s);
			return (ret);
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
	const	ssize_t	len = ft_strlen(s);
	char	*input;
	char	*new_s;

	clear_lexer(lexer);
	init_lexer(lexer);
	input = readline("> ");
	if (input == NULL)
		return ((errno == 0) - 1);
	if (s[len - 1] == '\\' && quote_error(s) == 0)
	{
		s[len - 1] = '\0';
		new_s = ft_strjoin(s, input);
	}
	else
		new_s = ft_strjoin_three(s, "\n", input);
	free(input);
	if (new_s == NULL)
		return (-1);
	if (fill_lexer(lexer, new_s) == -1)
	{
		free(new_s);
		return (-1);
	}
	free(new_s);
	return (len - 1);
}

static	int	quote_error(char *s)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (is_quote(*s))
		{
			ret = to_next_quote(s);
			if (ret == 0)
				return (1);
			s += ret;
		}
		else
			++s;
	}
	return (0);
}
