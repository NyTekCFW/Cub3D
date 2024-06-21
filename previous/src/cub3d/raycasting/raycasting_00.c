/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:14:10 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/20 11:03:42 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	flashlight(t_shaders *sh, t_ray *ray, t_vec2 v, __uint32_t c)
{
	t_ml	*lx;
	double	xdist;
	t_vec2f	center;
	t_vec2f	vf;
	double	a;

	lx = gmlx(ACT_GET);
	if (lx && sh)
	{
		center = (t_vec2f){sh->img.width / 2, sh->img.height / 2};
		vf = (t_vec2f){v.x, v.y};
		xdist = dist(center, vf);
		if (xdist <= 85.0 + ray->pwall_dist)
		{
			a = exp(-0.05 * xdist) + (0.8 / (ray->pwall_dist + 1));
			if (xdist > 85.0)
				a *= 1.0 - (xdist - 85.0) / (85.0 / 2.0);
			a = fmax(0.0, fmin(a, 1.0));
			set_color(&sh->img, get_px_adr(&sh->img, v), blend_colors(c, 0xffffff, a));
		}
	}
}

static void	draw_line(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh;
	int			y;

	sh = get_img("framework");
	//ceiling
	y = ray->draw_start - 1;
	while (y >= 0)
	{
		set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), blend_colors(0x00ffff, 0x030303, (float)y / (float)ray->draw_end));
		if (p->flashlight == 1) 
			flashlight(sh, ray, (t_vec2){x, y}, 0x00ffff);
		y--;
	}
	//floor render
	y = sh->img.height - 1;
	while (y >= ray->draw_end)
	{
		set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), blend_colors(0x00ff00, 0x030303, 1 - ((float)y / (float)sh->img.height)));
		if (p->flashlight == 1)
			flashlight(sh, ray, (t_vec2){x, y}, 0x00ff00);
		y--;
	}
	//wall render
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->color = 0x440033;
		set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), blend_colors(ray->color, 0x030303, ray->pwall_dist / 15));
		if (p->flashlight == 1)
			flashlight(sh, ray, (t_vec2){x, y}, ray->color);
		y++;
	}
}

static void	ray_line(t_ray *ray, t_cb *cub, t_ml *lx)
{
	if (ray->side == 0)
		ray->pwall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->pwall_dist = (ray->side_dist.y - ray->delta_dist.y);
	ray->line_height = (int)(lx->height / ray->pwall_dist);
	ray->draw_start = (-ray->line_height / 2) + (lx->height / 2) + ((lx->height / 2) * tan(cub->player.vangle));
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (lx->height / 2) + ((lx->height / 2) * tan(cub->player.vangle));
	if (ray->draw_end >= lx->height)
		ray->draw_end = lx->height - 1;
	if (ray->side == 0)
		ray->wall_x = cub->player.origin.y + ray->pwall_dist * ray->dir.y;
	else
		ray->wall_x = cub->player.origin.x + ray->pwall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
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

static void	init_ray(t_ray *ray, t_cb *cub, t_ml *lx, int x)
{
	t_player	*player;

	player = &cub->player;
	ray->camera = (2 * x) / (double)lx->width - 1;
	ray->dir.x = player->dir.x + player->plane.x * ray->camera;
	ray->dir.y = player->dir.y + player->plane.y * ray->camera;
	ray->map = (t_vec2){(int)player->origin.x, (int)player->origin.y};
	ray->delta_dist = (t_vec2f){fabs(1 / ray->dir.x), fabs(1 / ray->dir.y)};
	ray->hit = 0;
	ray_dda_step(ray, player);
	ray_dda_hit(ray, cub);
	ray_line(ray, cub, lx);
	if (ray->draw_end >= 0 && ray->draw_end < lx->height)
		draw_line(x, ray, player);
}

/// @brief using raycasting to build the environnement based on player view 
void	raycast_env(void)
{
	t_ray	ray;
	t_cb	*cub;
	t_ml	*lx;
	int		x;

	lx = gmlx(ACT_GET);
	cub = g_cub(ACT_GET);
	x = 0;
	xmemset(&ray, 0, sizeof(t_ray));
	if (lx && cub)
	{
		fill_img_color(&get_img("framework")->img, 0);
		while (x < lx->width)
		{
			init_ray(&ray, cub, lx, x);
			x++;
		}
	}
}
