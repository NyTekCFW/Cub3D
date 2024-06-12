/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 05:57:57 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/12 07:13:01 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	player_assets(t_cb *cub, t_vec2 v)
{
	cub->player.origin = (t_vec2f)
	{v.x * cub->minimap.dimension, v.y * cub->minimap.dimension};
	cub->player.dir = (t_vec2f){-1, 0};
	cub->player.plane = (t_vec2f){0, 0.66};
	cub->player.vangle = 0;
	cub->player.weapon.ammo_clip = 300;
	cub->player.weapon.ammo_stock = 240;
	cub->player.weapon.max_ammo_clip = 300;
	cub->player.weapon.max_ammo_stock = 240;
	cub->player.weapon.debugname = 0xFFFFFF;
	cub->player.weapon.id = 0;
	cub->player.weapon.type = 2;
}

void	player_settings(t_cb *cub)
{
	t_vec2	v;

	v = (t_vec2){0, 0};
	while (v.y < cub->map_data.height)
	{
		v.x = 0;
		while (v.x < cub->map_data.width)
		{
			if (cub->map_data.map[v.y][v.x] == '4')
			{
				cub->map_data.map[v.y][v.x] = '0';
				player_assets(cub, v);
			}
			v.x++;
		}
		v.y++;
	}
}
