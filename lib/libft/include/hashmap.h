/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouble <ccouble@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 04:27:10 by ccouble           #+#    #+#             */
/*   Updated: 2024/03/03 05:26:00 by ccouble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# define HASHMAP_SIZE 2048

# include "vector.h"

typedef struct s_pair
{
	char	*key;
	char	*value;
}	t_pair;

typedef struct s_hashmap
{
	t_vector	map[HASHMAP_SIZE];
}	t_hashmap;

void	init_hashmap(t_hashmap *hashmap);
void	destroy_hashmap(t_hashmap *hashmap);
size_t	hash_key(char *key);
int		setvalue_hashmap(t_hashmap *hashmap, char *key, char *value);
char	*getvalue_hashmap(t_hashmap *hashmap, char *key);

#endif
