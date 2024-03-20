/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:19:20 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/20 01:27:09 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell $> "

# include "env.h"
# include "lexer.h"

typedef struct s_ms
{
	t_env	env;
}	t_ms;

int	parse_input(t_env *env, t_lexer *lexer, char *input);

#endif
