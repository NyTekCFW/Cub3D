/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:07:00 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/19 15:10:52 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "openmlx.h"
# include "cub3d_wpn.h"

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
	double	wall_x;
	t_vec2f	dir;
	t_vec2f	side_dist;
	t_vec2f	delta_dist;
	t_vec2	map;
	t_vec2	step;
}	t_ray;

//minimap
typedef struct mm_s
{
	t_vec2f	porigin;
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
	int			health;
	int			score;
	int			flashlight;
	t_vec2f		origin;
	t_vec2f		dir;
	t_vec2f		plane;
	double		vangle;
	t_weapon	*weapon;
}	t_player;


typedef struct map_s
{
	char	**map;
	int		width;
	int		height;
	int		dimension;
	int		envdist;
}	t_map;



typedef struct cb_s
{
	t_mm			minimap;
	t_map			map_data;
	t_player		player;
	t_weapon_data	weapons[4];
}	t_cb;

t_cb	*g_cub(int act);
//minimap
int		check_move(t_cb *cub, t_vec2 v);
void	minimap_settings(t_cb *cub);
void	player_settings(t_cb *cub);
void	map_init(t_cb *cub);
void	draw_cone(void);
void	player_init(void);
void	raycast_env(void);
void	cone_begin(t_map *data, t_player *p, t_mm *mm, t_prim *g);
void	build_minimap(void);
#endif