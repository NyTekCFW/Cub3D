/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:13:43 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/06 06:33:41 by lchiva           ###   ########.fr       */
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

float	deg_to_rad(int a)
{
	return ((a * PI) / 180.0);
}

int	fix_angle(int a)
{
	if (a > 359)
		a -= 360;
	else if (a < 0)
		a += 360;
	return (a);
}
