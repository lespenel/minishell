/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:30:21 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/04 09:25:33 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "hashmap.h"
#include <stdio.h>

char	*ms_getenv(t_env *env, char *key)
{
	return (getvalue_hashmap(env, key));
}
