/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:54:52 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/09 18:48:54 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	minimap_texture(char c, t_prim *s)
{
	if (c == '1' || c == '0' || c == '4')
	{
		if (c == '1')
		{
			ml_settexture(s, "/brick_argb.xpm");
			ml_color(s, 0xFF0000);
			ml_setintensity(s, 0.2);
		}
		else if (c == '0' || c == '4')
		{
			ml_settexture(s, "/ground.xpm");
			ml_color(s, 0);
			ml_setintensity(s, 0.4);
		}
		ml_savemesh(s, get_img("icon_minimap"));
		ml_end(s);
	}
}

static void	minimap_vertex(t_cb *cub, t_prim *s, t_vec4 v)
{
	char	**map;
	int		dim;
	//int		width;

	map = cub->map_data.map;
	dim = cub->minimap.dimension;
//	width = cub->map_data.width;
	v.z = (v.x * dim);
	v.w = (v.y * dim);
	ml_vertex(s, (t_vec2){v.z, v.w});
	ml_vertex(s, (t_vec2){v.z, v.w + dim});
	ml_vertex(s, (t_vec2){v.z + dim, v.w + dim});
	ml_vertex(s, (t_vec2){v.z + dim, v.w});
	ml_setmode(s, cub->minimap.minimap_wireframe);
	minimap_texture(map[v.y][v.x], s);
}

static void	minimap_skip(t_cb *cub, int a, t_prim *s, t_vec4 v)
{
	char	**map;
	//int		width;

	map = cub->map_data.map;
	//width = cub->map_data.width;
	v.y = 0;
	while (v.y < cub->map_data.height)
	{
		v.x = 0;
		while (v.x < cub->map_data.width)
		{
			*s = ml_begin(ML_PRIM_QUADS);
			if (map[v.y][v.x] == (a + 0x30))
				minimap_vertex(cub, s, v);
			v.x++;
		}
		v.y++;
	}
}

void	build_minimap(void)
{
	t_cb	*cub;
	t_prim	c;
	t_vec4	v;
	int		a;

	v = (t_vec4){0, 0, 0, 0};
	cub = g_cub(ACT_GET);
	if (cub)
	{
		a = 0;
		while (a < 5)
		{
			minimap_skip(cub, a, &c, v);
			a++;
		}
	}
}
