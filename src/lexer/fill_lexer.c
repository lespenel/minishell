/* ************************dd************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:02:31 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/14 23:32:19 by lespenel         ###   ########.fr       */
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

static int remove_nl(t_vector *new_s)
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
		if (s[i] == '\\' && quote == '\'' && s[i + 1])
			++i;
		else if (s[i] == '\\' && s[i + 1] && s[i + 1] != '\n')
			++i;
		else if (ft_strncmp(s + i, "\\\n", 2) == 0)
		{
			printf("sexe\n");
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
		printf("error add\n");
		return (NULL);
	}
	remove_nl(&new_s);
	return (new_s.array);
}
