/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:07:00 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/08 20:17:14 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "openmlx.h"

typedef struct ray_s
{
	int		rc;
	int		dof;
	float	ra;
	float	disv;
	float	dish;
	float	tn;
	float	vtn;
	float	frac;
	t_vec3	m;
	t_vec2f	v;
	t_vec2f	r;
	t_vec2f	o;
	t_vec2f	h;
}	t_ray;

//minimap
typedef struct mm_s
{
	t_vec2	origin;
	int		dimension;
	int		cone_wireframe;
	int		minimap_wireframe;
	int		width;
	int		height;
	int		size;
	int		min;
}	t_mm;

typedef struct player_s
{
	t_vec2f	pad;
	t_vec2f	origin;
	float	angle;
}	t_player;

typedef struct map_s
{
	char	map[90];
	int		width;
	int		height;
	int		dimension;
}	t_map;

typedef struct cb_s
{
	t_mm		minimap;
	t_map		map_data;
	t_player	player;
}	t_cb;

t_cb	*g_cub(int act);
//minimap
void	build_images(void);
void	minimap_settings(t_cb *cub);
void	map_init(t_cb *cub);
void	player_init(void);
void	cone_begin(t_map *data, t_player *p, t_mm *mm, t_prim *g);
void	build_minimap(void);
#endif
