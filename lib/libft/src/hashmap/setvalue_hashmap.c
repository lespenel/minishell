/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setvalue_hashmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 05:26:14 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/03 05:44:00 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "vector.h"

int	setvalue_hashmap(t_hashmap *hashmap, char *key, char *value)
{
	const size_t	hash = hash_key(key) % HASHMAP_SIZE;
	t_pair			pair;

	pair.key = key;
	pair.value = value;
	return (add_vector(hashmap->map + hash, &pair, 1));
}
