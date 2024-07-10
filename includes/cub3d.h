/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:24:21 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/08 22:52:09 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "openmlx.h"
# include "cub3d_wpn.h"
# include "cub3d_dvars.h"
# include "cub3d_player.h"

enum e_cub_texture
{
	TEX_WALL_SOUTH	= 0,
	TEX_WALL_NORTH,
	TEX_WALL_EAST,
	TEX_WALL_WEST,
	TEX_GROUND,
	TEX_CEILING,
	TEX_RENDER
};

typedef struct area_s
{
	t_vec2	a1;
	t_vec2	a2;
	t_vec2	a3;
	t_vec2	a4;
	t_vec2	u;
}	t_area;

typedef struct screen_s
{
	int		x;
	int		y;
	t_area	area;
}	t_screen;

typedef struct ray_s
{
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;
	double		camera;
	double		pwall_dist;
	float		wall_x;
	t_vec2f		dir;
	t_vec2f		side_dist;
	t_vec2f		delta_dist;
	t_vec2		map;
	t_vec2		step;
	t_vec2		amp;
	t_shaders	**texture;
	double		var_shadow;
	double		var_aspect;
	double		var_lightradius;
	float		v_offset;
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


typedef struct map_s
{
	char	**map;
	int		width;
	int		height;
	int		dimension;
}	t_map;

typedef struct cb_s
{
	t_screen		screen;
	t_mm			minimap;
	t_map			map_data;
	t_player		player;
	t_dvars			vars[8];
	t_weapon_data	weapons[2];
	t_shaders		*texture[7];
	int				stop_handler;
}	t_cb;

//cub struct
t_cb		*g_cub(int act);
void		init_dvars(t_cb *cub);
void		initial_weapons_data(t_cb *cub);
void		initial_center_screen(t_cb *cub);
//screen
void		draw_safe_area(void);
void		safe_area_update(t_screen *sc);
//raycasting
void		raycast_env(void);
void		ray_get_color(t_ray *ray);
void		draw_ceiling(int x, t_ray *ray, t_player *p);
void		draw_floor(int x, t_ray *ray, t_player *p);
void		draw_walls(int x, t_ray *ray, t_player *p);
t_shaders	*get_walls_texture(t_ray *ray);
void		flashlight_move(t_vec2 *u);
__uint32_t	get_shadow(__uint32_t c, float dist);
//map
void		map_init(t_cb *cub);
//
int			check_move(t_cb *cub, t_vec2 v);
void		player_settings(t_cb *cub);
//
void		hud_render(void);
void		crosshair_hud(t_cb *cub, t_shaders *sh);
#endif