/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:25:25 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/28 19:36:46 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

t_vec2	*get_move_render(void)
{
	static t_vec2	amp = {0, 0};

	return (&amp);
}

__uint32_t	get_shadow(__uint32_t c, float dist)
{
	if (dist >= 1.0)
		c = 0x030303;
	else
		c = blend_colors(c, 0x030303, dist);
	return (c);
}

/// @brief (ray->dir.x < 0) = WEST | (ray->dir.y > 0) = SOUTH
void	ray_get_color(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir.x < 0)
			ray->color = 0x0000FF;
		else
			ray->color = 0xFFFF00;
	}
	else
	{
		if (ray->dir.y > 0)
			ray->color = 0x00FFFF;
		else
			ray->color = 0xFF00FF;
	}
}
