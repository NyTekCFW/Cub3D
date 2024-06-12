/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:07:00 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/12 06:34:52 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "openmlx.h"

typedef struct ray_s
{
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	double	camera;
	double	pwall_dist;
	t_vec2f	dir;
	t_vec2f	side_dist;
	t_vec2f	delta_dist;
	t_vec2	map;
	t_vec2	step;
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

typedef struct weapon_s
{
	__uint32_t	debugname;
	char		weaponname[32];
	int			id;
	int			type;
	__uint32_t	ammo_stock;
	__uint32_t	ammo_clip;
	__uint32_t	max_ammo_stock;
	__uint32_t	max_ammo_clip;
}	t_weapon;

typedef struct player_s
{
	t_vec2f		origin;
	t_vec2f		dir;
	t_vec2f		plane;
	double		vangle;
	t_weapon	weapon;
}	t_player;


typedef struct map_s
{
	char	**map;
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
void	player_settings(t_cb *cub);
void	map_init(t_cb *cub);
void	draw_cone(void);
void	player_init(void);
void	raycasting(void);
void	cone_begin(t_map *data, t_player *p, t_mm *mm, t_prim *g);
void	build_minimap(void);
#endif
