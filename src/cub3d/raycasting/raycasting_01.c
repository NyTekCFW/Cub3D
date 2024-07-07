/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:21:23 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/07 22:57:18 by lchiva           ###   ########.fr       */
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

	sh = ray->texture[TEX_RENDER];//get_img("framework");
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

void draw_floor(int x, t_ray *ray, t_player *p)
{
    t_shaders *sh;
    t_shaders *floor;
    int y;
    __uint32_t c;
    __uint32_t s;
    double floor_x, floor_y;
    double row_distance;
    int tex_x, tex_y;

    sh = ray->texture[TEX_RENDER];
    floor = ray->texture[TEX_GROUND];

    if (sh && floor)
    {
        y = sh->img.height - 1;
        while (y >= ray->draw_end)
        {
			row_distance = 720.0 / (2.0 * y - 720.0 - 2.0 * ray->v_offset);
            floor_x = p->origin.x + row_distance * ray->dir.x;
            floor_y = p->origin.y + row_distance * ray->dir.y;
            tex_x = (int)(floor_x * floor->img.width) % floor->img.width;
            tex_y = (int)(floor_y * floor->img.height) % floor->img.height;
            s = *(__uint32_t *)(floor->img.addr + get_px_adr(&floor->img, (t_vec2){tex_x, tex_y}));
            c = get_shadow(s, (1 - ((float)y / (float)sh->img.height)) * ray->var_shadow);
            set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), c);
			if (p->flashlight == 1)
				flashlight(sh, ray, (t_vec2){x, y}, s);
			y--;
        }
    }
}



void draw_walls(int x, t_ray *ray, t_player *p)
{
    t_shaders *sh;
    t_shaders *wl;
    int y;
    __uint32_t c;
    __uint32_t s;
    int tex_x;
    int tex_y;
    float step;
    float tex_pos;

    sh = ray->texture[TEX_RENDER];
    wl = get_walls_texture(ray);
    if (sh && wl)
    {
        tex_x = (int)(ray->wall_x * (float)(wl->img.width));
        if (ray->side == 0 && ray->dir.x > 0)
            tex_x = wl->img.width - tex_x - 1;
        if (ray->side == 1 && ray->dir.y < 0)
            tex_x = wl->img.width - tex_x - 1;
        step = 1.0 * wl->img.height / ray->line_height;
		tex_pos = (ray->draw_start - (360 + (int)ray->v_offset) + ray->line_height / 2) * step;
	    y = ray->draw_start;
        while (y < ray->draw_end)
        {
            tex_y = (int)tex_pos & (wl->img.height - 1);
            tex_pos += step;
            s = *(__uint32_t *)(wl->img.addr + get_px_adr(&wl->img, (t_vec2){tex_x, tex_y}));
           c = get_shadow(s, (ray->pwall_dist / 15) * ray->var_shadow);
            set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), c);
            if (p->flashlight == 1)
				flashlight(sh, ray, (t_vec2){x, y}, s);
			y += 1;
        }
    }
}

/*
void draw_ceiling(int x, t_ray *ray, t_player *p)
{
    t_shaders *sh;
    t_shaders *ceiling;
    int y;
    __uint32_t c;
    __uint32_t s;
    double ceiling_x, ceiling_y;
    double row_distance;
    int tex_x, tex_y;
    
    sh = ray->texture[TEX_RENDER];
    ceiling = ray->texture[TEX_CEILING];
    if (sh && ceiling)
    {
        y = ray->draw_start - 1;
        while (y >= 0)
        {
			row_distance = 720.0 / (2.0 * y - 720.0 - 2.0 * ray->v_offset);

            ceiling_x = p->origin.x + row_distance * ray->dir.x;
            ceiling_y = p->origin.y + row_distance * ray->dir.y;

            // Convert real-world coordinates to texture coordinates
            tex_x = (int)(ceiling_x * ceiling->img.width) % ceiling->img.width;
            tex_y = (int)(ceiling_y * ceiling->img.height) % ceiling->img.height;

            // Handle negative texture coordinates
            if (tex_x < 0) tex_x += ceiling->img.width;
            if (tex_y < 0) tex_y += ceiling->img.height;

            // Get the color from the texture
            s = *(__uint32_t *)(ceiling->img.addr + get_px_adr(&ceiling->img, (t_vec2){tex_x, tex_y}));
            c = get_shadow(s, ((float)y / (float)ray->draw_end) * ray->var_shadow);

            // Set the color of the pixel on the screen
            set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), c);

            if (p->flashlight == 1)
                flashlight(sh, ray, (t_vec2){x, y}, s);

            y--;
        }
    }
}
*/