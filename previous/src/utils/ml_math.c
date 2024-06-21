/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:13:43 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/07 23:42:21 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

void	set_value(void *adr, __uint32_t val)
{
	*(__uint32_t *)adr = val;
}

__uint32_t	get_value(void *adr)
{
	return (*(__uint32_t *)adr);
}

float	dist(t_vec2f a, t_vec2f b)
{
	return (sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}
