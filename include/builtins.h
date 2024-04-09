/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:27:17 by lespenel          #+#    #+#             */
/*   Updated: 2024/04/10 01:55:26 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"
# include "minishell.h"
# include "lexer.h"

# define CMD_NOT_FOUND "minishell: %s: command not found\n"

typedef enum e_builtins_type
{
	MS_ECHO,
	MS_CD,
	MS_PWD,
	MS_EXPORT,
	MS_UNSET,
	MS_ENV,
	MS_EXIT,
}	t_builtins_type;

typedef int	(*t_builtin)(t_env *env, char **args);

typedef struct s_builtins_map
{
	char		*name;
	t_builtin	func;
}	t_buitlins_map;

int		get_argc(char **args);
int		is_builtin(char *word);
int		exec_builtins(t_ms *minishell, t_lexer *lexer, char **args);

int		ms_cd(t_env	*env, char **args);
int		ms_echo(t_env *env, char **args);
int		ms_env(t_env *env, char **args);
int		ms_exit(t_ms *minishell, t_lexer *lexer, char **args);
int		ms_export(t_env *env, char **args);
int		ms_pwd(t_env *env, char **args);
int		ms_unset(t_env *env, char **args);

#endif
