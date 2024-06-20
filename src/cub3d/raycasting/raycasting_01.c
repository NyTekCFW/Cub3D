/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:21:23 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/20 13:25:16 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	flashlight_move(t_vec2 *u)
{
	static t_vec2	t = {1, -1};

	u->x += t.x;
	u->y += t.y;
	if (u->x >= 15 || u->x <= -15)
		t.x *= -1;
	if (u->y >= 10 || u->y <= -10)
		t.y *= -1;
}

static void	flashlight(t_shaders *sh, t_ray *ray, t_vec2 v, __uint32_t c)
{
	t_ml	*lx;
	double	xdist;
	t_vec2f	center;
	double	a;

	lx = gmlx(ACT_GET);
	if (lx && sh)
	{
		center = (t_vec2f){(sh->img.width / 2) + ray->amp.x,
				(sh->img.height / 2) + ray->amp.y};
		xdist = dist(center, (t_vec2f){v.x, v.y});
		if (xdist <= 85.0 + ray->pwall_dist)
		{
			a = exp(-0.05 * xdist) + (0.8 / (ray->pwall_dist + 1));
			if (xdist > 85.0)
				a *= 1.0 - (xdist - 85.0) / (85.0 / 2.0);
			a = fmax(0.0, fmin(a, 1.0));
			set_color(&sh->img, get_px_adr(&sh->img, v),
				blend_colors(c, 0xffffff, a));
		}
	}
}

void	draw_ceiling(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh;
	int			y;

	sh = get_img("framework");
	if (sh)
	{
		y = ray->draw_start - 1;
		while (y >= 0)
		{
			set_color(&sh->img, get_px_adr(&sh->img,
					(t_vec2){x, y}), blend_colors(0xb82000, 0x030303,
					(float)y / (float)ray->draw_end));
			if (p->flashlight == 1)
				flashlight(sh, ray, (t_vec2){x, y}, 0xb82000);
			y--;
		}
	}
}

void	draw_floor(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh;
	int			y;

	sh = get_img("framework");
	if (sh)
	{
		y = sh->img.height - 1;
		while (y >= ray->draw_end)
		{
			set_color(&sh->img, get_px_adr(&sh->img,
					(t_vec2){x, y}), blend_colors(0x00ff00, 0x030303,
					1 - ((float)y / (float)sh->img.height)));
			if (p->flashlight == 1)
				flashlight(sh, ray, (t_vec2){x, y}, 0x00ff00);
			y--;
		}
	}
}

void	draw_walls(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh;
	int			y;

	sh = get_img("framework");
	if (sh)
	{
		y = ray->draw_start;
		while (y < ray->draw_end)
		{
			set_color(&sh->img, get_px_adr(&sh->img,
					(t_vec2){x, y}), blend_colors(ray->color,
					0x030303, ray->pwall_dist / 15));
			if (p->flashlight == 1)
				flashlight(sh, ray, (t_vec2){x, y}, ray->color);
			y++;
		}
	}
}
