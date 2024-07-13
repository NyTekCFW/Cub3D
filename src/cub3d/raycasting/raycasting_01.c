/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:21:23 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/13 11:59:52 by lchiva           ###   ########.fr       */
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

void	flashlight(t_shaders *sh, t_ray *ray, t_vec2 v, __uint32_t c)
{
	double	xdist;
	t_vec2f	center;
	double	a;
	double	radius;

	if (sh)
	{
		radius = ray->var_lightradius;
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

	sh = ray->texture[TEX_RENDER];
	if (sh)
	{
		y = ray->draw_start - 1;
		while (y >= 0)
		{
			c = get_shadow(0xb82000,
					((float)y / (float)ray->draw_end) * ray->var_shadow);
			if (c != 0xb82000)
				set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), c);
			if (p->flashlight == 1)
				flashlight(sh, ray, (t_vec2){x, y}, 0xb82000);
			y -= 1;
		}
	}
}

void	_draw_floor(t_ray *ray, t_vec2 u, t_shaders	*sh[], t_player *p)
{
	__uint32_t	c[2];
	t_vec2f		floor;
	t_vec2		tex;
	double		row;

	row = 720.0 / (2.0 * u.y - 720.0 - 2.0 * ray->v_offset);
	floor.x = p->origin.x + row * ray->dir.x;
	floor.y = p->origin.y + row * ray->dir.y;
	tex.x = (int)(floor.x * sh[1]->img.width) % sh[1]->img.width;
	tex.y = (int)(floor.y * sh[1]->img.height) % sh[1]->img.height;
	c[0] = *(__uint32_t *)(sh[1]->img.addr + get_px_adr(&sh[1]->img, tex));
	c[1] = get_shadow(c[0], (1 - ((float)u.y / (float)sh[0]->img.height))
			* ray->var_shadow);
	set_color(&sh[0]->img, get_px_adr(&sh[0]->img, u), c[1]);
	if (p->flashlight == 1)
		flashlight(sh[0], ray, u, c[0]);
}

void	draw_floor(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh[2];
	int			y;

	sh[0] = ray->texture[TEX_RENDER];
	sh[1] = ray->texture[TEX_GROUND];
	if (sh[0] && sh[1])
	{
		y = sh[0]->img.height;
		while (--y >= ray->draw_end)
			_draw_floor(ray, (t_vec2){x, y}, sh, p);
	}
}
