/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 01:50:01 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/06 05:08:16 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int smapx=9, smapy=9, smaps=64;
int smap[] =
{
	1,1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,1,
	1,0,0,0,4,0,0,0,1,
	1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,
};

static void	asset_origin(t_cb *cub, t_vec2 p)
{
	cub->player.mm_origin = (t_vec2){(p.x * \
	cub->minimap.dimension) + cub->minimap.origin.x, (p.y \
	* cub->minimap.dimension) + cub->minimap.origin.y};
	cub->player.origin = p;
}

void	get_porigin(void)
{
	t_cb	*cub;
	t_vec2	p;

	p = (t_vec2){0, 0};
	cub = g_cub(ACT_GET);
	if (cub)
	{
		while (p.y < 9)
		{
			p.x = 0;
			while (p.x < 9)
			{
				if (smap[p.y * smapx + p.x] == 4)
				{
					smap[p.y * smapx + p.x] = 0;
					asset_origin(cub, p);
					return ;
				}
				p.x++;
			}
			p.y++;
		}
	}
}
