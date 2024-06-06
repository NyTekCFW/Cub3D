/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:03:40 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/06 06:22:19 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int wmapx=9, wmapy=9, wmaps=64;
int wmap[] =
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

static void	gen_player(void)
{
	t_cb	*cub;
	t_prim	p;
	t_vec4	v;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		v = (t_vec4){cub->player.mm_origin.x, cub->player.mm_origin.y, 0, 0};
		v.z = cub->player.mm_origin.x;
        v.w = cub->player.mm_origin.y;
		
		printf("Player Origin: (%i, %i)\n", v.x, v.y);
        printf("Minimap Position: (%i, %i) %f\n", v.z, v.w, cub->minimap.scale);
		/*
		

		if (v.z < cub->minimap.origin.x + 20)
			v.z = cub->minimap.origin.x + 20;
		if (v.w < cub->minimap.origin.y + 20)
			v.w = cub->minimap.origin.y + 20;
		if (v.z > cub->minimap.origin.x + cub->minimap.width + 32)
			v.z = cub->minimap.origin.x + cub->minimap.width + 32;
		if (v.w > cub->minimap.origin.y + cub->minimap.height + 32)
			v.w = cub->minimap.origin.y + cub->minimap.height + 32;*/
		p = ml_begin(ML_PRIM_POINTS);
		ml_size(&p, 8);
		ml_vertex(&p, (t_vec2){v.z, v.w});
		ml_color(&p, 0xFFFFFF);
		ml_settexture(&p, "/link_head.xpm");
		ml_size(&p, 13 * cub->minimap.scale);
		ml_setwrap(&p, ML_WRAP_REPEAT_CENTER);
		ml_end(&p);
	}
}

void	generate_minimap(void)
{
	t_cb	*cub;
	t_prim	c;
	t_vec4	v;
	int		dim;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		v = (t_vec4){0, 0, 0, 0};
		dim = cub->minimap.dimension;
		while (v.y < wmapy)
		{
			v.x = 0;
			while (v.x < wmapx)
			{
				c = ml_begin(ML_PRIM_QUADS);
				v.z = (v.x * dim) + cub->minimap.origin.x;
				v.w = (v.y * dim) + cub->minimap.origin.y;
				ml_vertex(&c, (t_vec2){v.z, v.w});
				ml_vertex(&c, (t_vec2){v.z, v.w + dim});
				ml_vertex(&c, (t_vec2){v.z + dim, v.w + dim});
				ml_vertex(&c, (t_vec2){v.z + dim, v.w});
				ml_settexture(&c, "/ground.xpm");
				if (wmap[v.y * wmapx + v.x] == 1)
					ml_color(&c, 0xFFFFFF);
				else
					ml_color(&c, 0);
				ml_setintensity(&c, 0.4);
				ml_end(&c);
				v.x++;
			}
			v.y++;
		}
		gen_player();
	}
}
