/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespenel <lespenel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:14:10 by lespenel          #+#    #+#             */
/*   Updated: 2024/03/04 13:29:23 by lespenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
