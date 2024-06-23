/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:25:25 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/21 17:00:08 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	ray_get_color(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir.x < 0)//WEST
			ray->color = 0x0000FF;
		else//EST
			ray->color = 0xFFFF00;
	}
	else
	{
		if (ray->dir.y > 0)//SOUTH
			ray->color = 0x00FFFF;
		else//NORTH
			ray->color = 0xFF00FF;
	}
}
