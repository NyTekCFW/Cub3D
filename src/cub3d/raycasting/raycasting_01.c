/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:21:23 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/28 20:03:11 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	flashlight_move(t_vec2 *u)
{
	static t_vec2	t = {1, -1};

	u->x += t.x;
	u->y += t.y;
	if (u->x >= 8 || u->x <= -8)
		t.x *= -1;
	if (u->y >= 5 || u->y <= -5)
		t.y *= -1;
}

static void	flashlight(t_shaders *sh, t_ray *ray, t_vec2 v, __uint32_t c)
{
	double	xdist;
	t_vec2f	center;
	double	a;
	double	radius;

	if (sh)
	{
		radius = getvar(VAR_FLASHLIGHT_RADIUS);
		center = (t_vec2f){(sh->img.width / 2) + ray->amp.x,
			(sh->img.height / 2) + ray->amp.y};
		xdist = dist(center, (t_vec2f){v.x, v.y});
		if (xdist <= radius + ray->pwall_dist)
		{
			a = expf(-0.05 * xdist) + (0.8 / (ray->pwall_dist + 1));
			if (xdist > radius)
				a *= 1.0 - (xdist - radius) / (radius / 2.0);
			a = fmaxf(0.0, fminf(a, 1.0));
			set_color(&sh->img, get_px_adr(&sh->img, v),
				blend_colors(c, 0xffffff, a));
		}
	}
}

void	draw_ceiling(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh;
	int			y;
	__uint32_t	c;
	double		var;

	sh = get_img("framework");
	var = getvar(VAR_SHADOWS);
	if (sh)
	{
		y = ray->draw_start - 1;
		while (y >= 0)
		{
			c = get_shadow(0xb82000,
					((float)y / (float)ray->draw_end) * var);
			if (c != 0xb82000)
				set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), c);
			if (p->flashlight == 1)
				flashlight(sh, ray, (t_vec2){x, y}, 0xb82000);
			y -= 1;
		}
	}
}

void	draw_floor(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh;
	int			y;
	__uint32_t	c;

	sh = get_img("framework");
	if (sh)
	{
		y = sh->img.height - 1;
		while (y >= ray->draw_end)
		{
			c = get_shadow(0x00ff00, (1 - ((float)y / (float)sh->img.height))
					* getvar(VAR_SHADOWS));
			set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), c);
			c = get_shadow(0x00ff00, (1 - ((float)(y - 1) / (float)sh->img.height))
					* getvar(VAR_SHADOWS));
			set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, (y - 1)}), c);
			if (p->flashlight == 1)
			{
				flashlight(sh, ray, (t_vec2){x, y}, 0x00ff00);
				flashlight(sh, ray, (t_vec2){x, y - 1}, 0x00ff00);
			}
			y -= 2;
		}
	}
}

void	draw_walls(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh;
	int			y;
	__uint32_t	c;

	sh = get_img("framework");
	if (sh)
	{
		y = ray->draw_start;
		while (y < ray->draw_end)
		{
			c = get_shadow(ray->color, (ray->pwall_dist / 15)
					* getvar(VAR_SHADOWS));
			set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), c);
			set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y + 1}), c);
			if (p->flashlight == 1)
			{
				flashlight(sh, ray, (t_vec2){x, y}, ray->color);
				flashlight(sh, ray, (t_vec2){x, y + 1}, ray->color);
			}
			y += 2;
		}
	}
}
