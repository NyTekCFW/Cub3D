/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 05:57:57 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/16 23:58:39 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	player_assets(t_cb *cub, t_vec2 v)
{
	cub->player.origin = (t_vec2f)
	{(double)(v.x * cub->map_data.envdist), (double)(v.y * cub->map_data.envdist * 1.2)};
	cub->player.dir = (t_vec2f){-1, 0};
	cub->player.plane = (t_vec2f){0, 0.66};
	cub->player.vangle = 0;
	cub->player.health = 130;
	cub->player.score = 500;
	xalloc((void **)&cub->player.weapon, sizeof(t_weapon), 1);
	give_weapon("M1911");
}

void	player_settings(t_cb *cub)
{
	t_vec2	v;

	v = (t_vec2){0, 0};
	while (v.y < cub->map_data.height && cub->map_data.map[v.y])
	{
		v.x = 0;
		while (v.x < cub->map_data.width && cub->map_data.map[v.y][v.x])
		{
			if (cub->map_data.map[v.y][v.x] == '4')
			{
				cub->map_data.map[v.y][v.x] = '0';
				player_assets(cub, v);
				break ;
			}
			v.x++;
		}
		v.y++;
	}
}
