/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:13:43 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/02 02:23:30 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief apply val at the adr
/// @param adr memory address
/// @param val value in unsigned int
void	set_value(void *adr, __uint32_t val)
{
	*(__uint32_t *)adr = val;
}

/// @brief return value at adr
/// @param adr memory address
/// @return 
__uint32_t	get_value(void *adr)
{
	return (*(__uint32_t *)adr);
}

/// @brief distance between 2 position (x, y)
/// @param a position 1 in t_vec2f (x, y)
/// @param b position 2 in t_vec2f (x, y)
/// @return distance in float
float	dist(t_vec2f a, t_vec2f b)
{
	return (sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}
