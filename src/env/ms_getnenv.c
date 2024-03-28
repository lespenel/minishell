/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:29:34 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/20 01:30:24 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "hashmap.h"

char	*ms_getnenv(t_env *env, char *key, size_t n)
{
	return (getvaluen_hashmap(env, key, n));
}
