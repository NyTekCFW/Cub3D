/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:54:53 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/08 20:37:10 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	minimap_rescale(t_mm *mm, t_map *mp)
{
	mm->width = (mm->dimension * mp->width);
	mm->height = (mm->dimension * mp->height);
}

static void	minimap_scaling(t_mm *mm, t_map *mp)
{
	minimap_rescale(mm, mp);
	while (mm->width > mm->size || mm->height > mm->size)
	{
		mm->dimension -= 1;
		if (mm->dimension <= mm->min)
		{
			mm->dimension = mm->min;
			minimap_rescale(mm, mp);
			return ;
		}
		minimap_rescale(mm, mp);
	}
}

void	minimap_settings(t_cb *cub)
{
	t_mm	*mm;
	t_map	*mp;

	if (cub)
	{
		mm = &cub->minimap;
		mp = &cub->map_data;
		mm->dimension = mp->dimension;
		mm->origin = (t_vec2){0, 0};
		mm->size = 150;
		mm->min = 21;
		mm->cone_wireframe = 1;
		mm->minimap_wireframe = 0;
		minimap_scaling(mm, mp);
	}
}

static void	minimap_vertex(t_cb *cub, t_prim *s, t_vec4 v)
{
	char	*map;
	int		dim;
	int		width;

	map = cub->map_data.map;
	dim = cub->minimap.dimension;
	width = cub->map_data.width;
	v.z = (v.x * dim);
	v.w = (v.y * dim);
	ml_vertex(s, (t_vec2){v.z, v.w});
	ml_vertex(s, (t_vec2){v.z, v.w + dim});
	ml_vertex(s, (t_vec2){v.z + dim, v.w + dim});
	ml_vertex(s, (t_vec2){v.z + dim, v.w});
	ml_settexture(s, "/ground.xpm");
	if (map[(v.y * width) + v.x] == '1')
		ml_color(s, 0xFFFFFF);
	else
	{
		ml_color(s, 0x00FF00);
		ml_setintensity(s, 0.4);
	}
	ml_savemesh(s, get_img("icon_minimap"));
	ml_setmode(s, cub->minimap.minimap_wireframe);
	ml_end(s);
}

void	build_minimap(void)
{
	t_cb	*cub;
	t_prim	c;
	t_vec4	v;

	v = (t_vec4){0, 0, 0, 0};
	cub = g_cub(ACT_GET);
	if (cub)
	{
		while (v.y < cub->map_data.height)
		{
			v.x = 0;
			while (v.x < cub->map_data.width)
			{
				c = ml_begin(ML_PRIM_QUADS);
				minimap_vertex(cub, &c, v);
				v.x++;
			}
			v.y++;
		}
	}
}
/*


typedef struct mm_s
{
	t_vec2	origin;
	float	scale;
	float	dim_scale;
	int		dimension;
	int		view_filled;
	int		width;
	int		height;
	int		size;
	int		min;
}	t_mm;*/