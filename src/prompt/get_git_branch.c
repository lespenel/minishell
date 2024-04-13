/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_git_branch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:22:41 by ccouble           #+#    #+#             */
/*   Updated: 2024/04/13 13:51:18 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minishell.h"
#include "prompt.h"
#include "ft_string.h"
#include <stdlib.h>

static int	add_git_branch(t_vector *prompt, char *branch);

int	get_git_branch(t_ms *ms, t_vector *prompt)
{
	static char	*argv[] = {"git", "branch", "--show-current", NULL};
	char		*result;

	result = get_command_result(ms, argv);
	if (result == NULL)
		return (-1);
	if (add_git_branch(prompt, result) == -1)
	{
		free(result);
		return (-1);
	}
	free(result);
	return (0);
}

static int	add_git_branch(t_vector *prompt, char *branch)
{
	if (ft_strlen(branch) == 0)
		return (0);
	if (add_color_to_prompt(prompt, WHT) == -1)
		return (-1);
	if (add_vector(prompt, " (", 2) == -1)
		return (-1);
	if (add_vector(prompt, branch, ft_strlen(branch) - 1) == -1)
		return (-1);
	if (add_vector(prompt, ")", 1) == -1)
		return (-1);
	return (0);
}
