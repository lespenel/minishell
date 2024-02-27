/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 05:55:50 by ccouble           #+#    #+#             */
/*   Updated: 2024/02/27 02:58:28 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IO_H
# define FT_IO_H

int		ft_putchar_fd(char c, int fd);
int		ft_putendl_fd(const char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(const char *s, int fd);
char	*get_next_line(int fd);

#endif
