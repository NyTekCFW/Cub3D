/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:03:57 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/13 11:29:35 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
/*
cell = (t_vec2){(x * cl->img.width) /
sh->img.width, (y * cl->img.height) / ray->draw_start};
c = blend_colors(get_px_color(&cl->img, cell), 0xFF0000, 0.4);
*/

static void	ray_line(t_ray *ray, t_cb *cub)
{
	if (ray->side == 0)
		ray->pwall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->pwall_dist = (ray->side_dist.y - ray->delta_dist.y);
	ray->line_height = (int)(720 / ray->pwall_dist);
	ray->draw_start = (-ray->line_height / 2) + 360 + ray->v_offset;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + 360 + ray->v_offset;
	if (ray->draw_end >= 720)
		ray->draw_end = 719;
	if (ray->side == 0)
		ray->wall_x = cub->player.origin.y + ray->pwall_dist * ray->dir.y;
	else
		ray->wall_x = cub->player.origin.x + ray->pwall_dist * ray->dir.x;
	ray->wall_x -= floorf(ray->wall_x);
}

static void	ray_dda_hit(t_ray *ray, t_cb *cub)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (check_move(cub, (t_vec2){ray->map.x, ray->map.y})
			&& cub->map_data.map[ray->map.y][ray->map.x] > '0')
			ray->hit = 1;
	}
}

static void	ray_dda_step(t_ray *ray, t_player *p)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (p->origin.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x
			= (ray->map.x + 1.0 - p->origin.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (p->origin.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y
			= (ray->map.y + 1.0 - p->origin.y) * ray->delta_dist.y;
	}
}

static void	init_ray(t_ray *ray, t_cb *cub, int x)
{
	t_player	*player;

	player = &cub->player;
	ray->camera = ((2 * x) / (float)1280 - 1)
		* (tanf(ray->var_aspect) * 1.777777778);
	ray->dir.x = player->dir.x + player->plane.x * ray->camera;
	ray->dir.y = player->dir.y + player->plane.y * ray->camera;
	ray->map = (t_vec2){(int)player->origin.x, (int)player->origin.y};
	ray->delta_dist = (t_vec2f){fabs(1 / ray->dir.x), fabs(1 / ray->dir.y)};
	ray->hit = 0;
	ray_dda_step(ray, player);
	ray_dda_hit(ray, cub);
	ray_line(ray, cub);
	if (ray->draw_end >= 0 && ray->draw_end < 720)
	{
		draw_ceiling(x, ray, player);
		draw_floor(x, ray, player);
		draw_walls(x, ray, player);
	}
}

/// @brief using raycasting to build the environnement based on player view 
void	raycast_env(void)
{
	t_ray		ray;
	t_cb		*cub;
	int			x;

	x = 0;
	cub = g_cub(ACT_GET);
	if (cub)
	{
		ray.var_shadow = getvar(VAR_SHADOWS);
		ray.var_aspect = getvar(VAR_ASPECT) / 2;
		ray.var_lightradius = getvar(VAR_FLASHLIGHT_RADIUS);
		ray.texture = cub->texture;
		ray.v_offset = tanf(cub->player.vangle) * 360;
		if (ray.texture[TEX_RENDER])
		{
			flashlight_move(get_move_render());
			fill_img_color(&ray.texture[TEX_RENDER]->img, 0xb82000);
			ray.amp = *get_move_render();
			while (x < 1280)
			{
				init_ray(&ray, cub, x);
				x++;
			}
		}
	}
}
