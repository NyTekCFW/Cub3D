/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:25:25 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 16:03:48 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/// @brief (ray->dir.x < 0) = WEST | (ray->dir.y > 0) = SOUTH
static t_shaders	*get_walls_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir.x < 0)
			return (ray->texture[TEX_WALL_WEST]);
		else
			return (ray->texture[TEX_WALL_EAST]);
	}
	else
	{
		if (ray->dir.y > 0)
			return (ray->texture[TEX_WALL_SOUTH]);
		else
			return (ray->texture[TEX_WALL_NORTH]);
	}
}

static void	_draw_walls(t_ray *ray, t_vec2 u, t_shaders	*sh[], t_player *p)
{
	__uint32_t	c[2];
	t_vec2		tex;
	float		step;
	float		pos;

	tex.x = (int)(ray->wall_x * (float)(sh[1]->img.width));
	if (ray->side == 0 && ray->dir.x > 0)
		tex.x = sh[1]->img.width - tex.x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		tex.x = sh[1]->img.width - tex.x - 1;
	step = 1.0 * sh[1]->img.height / ray->line_height;
	pos = (ray->draw_start - (360 + (int)ray->v_offset) + ray->line_height / 2)
		* step;
	u.y = ray->draw_start - 1;
	while (++u.y < ray->draw_end)
	{
		tex.y = (int)pos & (sh[1]->img.height - 1);
		pos += step;
		c[0] = *(__uint32_t *)(sh[1]->img.addr + get_px_adr(&sh[1]->img, tex));
		c[1] = get_shadow(c[0], (ray->pwall_dist / 15) * ray->var_shadow);
		set_color(&sh[0]->img, get_px_adr(&sh[0]->img, u), c[1]);
		if (p->flashlight == 1)
			flashlight(sh[0], ray, u, c[0]);
	}
}

t_vec2	*get_move_render(void)
{
	static t_vec2	amp = {0, 0};

	return (&amp);
}

__uint32_t	get_shadow(__uint32_t c, float dist)
{
	if (dist >= 1.0)
		c = 0x030303;
	else
		c = blend_colors(c, 0x030303, dist);
	return (c);
}

void	draw_walls(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh[2];

	sh[0] = ray->texture[TEX_RENDER];
	sh[1] = get_walls_texture(ray);
	if (sh[0] && sh[1])
		_draw_walls(ray, (t_vec2){x, 0}, sh, p);
}
