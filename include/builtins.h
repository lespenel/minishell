/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:27:17 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/14 23:23:50 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "lexer.h"

typedef enum e_builtins_type
{
	MS_ALIAS,
	MS_ECHO,
	MS_CD,
	MS_PWD,
	MS_EXPORT,
	MS_UNALIAS,
	MS_UNSET,
	MS_ENV,
	MS_EXIT,
}	t_builtins_type;

typedef int	(*t_builtin)(t_ms *ms, char **args);

typedef struct s_builtins_map
{
	char		*name;
	t_builtin	func;
}	t_buitlins_map;

int		get_argc(char **args);
int		is_builtin(char *word);
int		exec_builtins(t_ms *minishell, t_lexer_tok *token);

int		ms_alias(t_ms *ms, char **args);
int		ms_cd(t_ms	*ms, char **args);
int		ms_echo(t_ms *ms, char **args);
int		ms_env(t_ms *ms, char **args);
int		ms_exit(t_ms *minishell, t_lexer_tok *tok, char **args);
int		ms_export(t_ms *ms, char **args);
int		ms_pwd(t_ms *ms, char **args);
int		ms_unalias(t_ms *ms, char **args);
int		ms_unset(t_ms *ms, char **args);

#endif
