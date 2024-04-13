/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 05:43:42 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/13 15:54:13 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"
# define PROMPT "minishell $> "

char	*get_prompt(t_ms *ms);
int		add_color_to_prompt(t_vector *prompt, char *color);
int		add_pwd(t_ms *ms, t_vector *prompt);
char	*get_command_result(t_ms *ms, char **argv);
int		get_git_branch(t_ms *ms, t_vector *prompt);

#endif
