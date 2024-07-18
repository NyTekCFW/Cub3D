/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:06:45 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 10:30:07 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	check_move(t_cb *cub, t_vec2 v)
{
	if (v.x >= 0 && v.x < cub->map_data.width)
	{
		if (v.y >= 0 && v.y < cub->map_data.height)
			return (1);
	}
	return (0);
}

void	player_assets(t_cb *cub, t_vec2 v)
{
	cub->player.origin = (t_vec2f)
	{(double)v.x, (double)v.y * 1.2};
	cub->player.dir = (t_vec2f){-1, 0};
	cub->player.plane = (t_vec2f){0, 0.66};
	cub->player.vangle = 0;
	cub->player.health = 130;
	cub->player.score = 500;
	cub->player.speed = getvar(VAR_G_SPEED);
	p_reg_commands();
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
