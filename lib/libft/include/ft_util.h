/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:36:26 by ccouble           #+#    #+#             */
/*   Updated: 2024/01/08 03:15:58 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTIL_H
# define FT_UTIL_H

char	*ft_get_path(char *file, char *envp[]);
char	*ft_getenv(char *envp[], char *name);
void	ft_swap(int *a, int *b);

#endif
