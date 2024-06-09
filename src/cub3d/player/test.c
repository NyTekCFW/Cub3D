/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:47:29 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/09 20:55:39 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 4

char g_map[MAP_HEIGHT][MAP_WIDTH] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

void	draw_line(int x, int draw_start, int draw_end, int color)
{
	t_shaders	*sh;
	int			y;

	y = draw_start;
	sh = get_img("framework");
	while (y < draw_end)
	{
		set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), color);
		y++;
	}
}

void	ray_dda(t_ray *ray, t_cb *cub, t_ml *lx)
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
		if (cub->map_data.map[ray->map.y][ray->map.x] > '0')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->pwall_dist = (ray->map.x - cub->player.origin.x
				+ (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->pwall_dist = (ray->map.y - cub->player.origin.y
				+ (1 - ray->step.y) / 2) / ray->dir.y;
	ray->line_height = (int)(lx->height / ray->pwall_dist);
}

void	ray_step(t_ray *ray, t_cb *cub)
{
	t_player	*player;

	player = &cub->player;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->origin.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x
			= (ray->map.x + 1.0 - player->origin.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->origin.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y
			= (ray->map.y + 1.0 - player->origin.y) * ray->delta_dist.y;
	}
}

void	init_ray(t_ray *ray, t_ml *lx, t_cb *cub, int x)
{
	t_player	*player;

	player = &cub->player;
	ray->camera = 2 * x / (double)lx->width - 1;
	ray->dir.x = player->dir.x + player->plane.x * ray->camera;
	ray->dir.y = player->dir.y + player->plane.y * ray->camera;
	ray->map = (t_vec2){(int)player->origin.x, (int)player->origin.y};
	ray->delta_dist = (t_vec2f){fabs(1 / ray->dir.x), fabs(1 / ray->dir.y)};
	ray->hit = 0;
	ray_step(ray, cub);
	ray_dda(ray, cub, lx);
	ray->draw_start = (-ray->line_height / 2) + (lx->height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (lx->height / 2);
	if (ray->draw_end >= lx->height)
		ray->draw_end = lx->height - 1;
	ray->color = 0xFF0000;
	if (cub->map_data.map[ray->map.y][ray->map.x] != '1')
		ray->color = 0xFFFF00;
	if (ray->side == 1)
		ray->color = ray->color / 2;
	draw_line(x, ray->draw_start, ray->draw_end, ray->color);
}

void	raycasting(void)
{
	t_ray	ray;
	t_cb	*cub;
	t_ml	*lx;
	int		x;

	lx = gmlx(ACT_GET);
	cub = g_cub(ACT_GET);
	x = 0;
	if (lx && cub)
	{
		fill_img_color(&get_img("framework")->img, 0);
		while (x < lx->width)
		{
			init_ray(&ray, lx, cub, x);
			x++;
		}
	}
}
