/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:21:23 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/03 18:48:42 by lchiva           ###   ########.fr       */
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
void draw_walls(int x, t_ray *ray, t_player *p)
{
    t_shaders *sh;
    t_shaders *wl;
    int y;
    __uint32_t c;
    __uint32_t s;
    int tex_x;
    int tex_y;
    double step;
    double tex_pos;

    sh = get_img("framework");
    wl = get_walls_texture(ray);

    if (sh && wl)
    {
		if (ray->side == 0)
            ray->wall_x = p->origin.y + ray->pwall_dist * ray->dir.y;
        else
            ray->wall_x = p->origin.x + ray->pwall_dist * ray->dir.x;
        ray->wall_x -= floorf(ray->wall_x);
        // x coordinate on the texture
        tex_x = (int)(ray->wall_x * (float)(wl->img.width));
        if (ray->side == 0 && ray->dir.x > 0)
            tex_x = wl->img.width - tex_x - 1;
        if (ray->side == 1 && ray->dir.y < 0)
            tex_x = wl->img.width - tex_x - 1;
        step = 1.0 * sh->img.height / ray->line_height;
        int v_angle_offset = (int)(tanf(p->vangle) * 360.0);
		tex_pos = (ray->draw_start - (360 + v_angle_offset) + ray->line_height / 2) * step;
	    y = ray->draw_start;
        while (y < ray->draw_end)
        {
            tex_y = (int)tex_pos & (wl->img.height - 1);
            tex_pos += step;
            s = *(__uint32_t *)(wl->img.addr + get_px_adr(&wl->img, (t_vec2){tex_x, tex_y}));
            c = get_shadow(s, (ray->pwall_dist / 15) * getvar(VAR_SHADOWS));
            set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), c);
            set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y + 1}), c);

            if (p->flashlight == 1)
            {
                flashlight(sh, ray, (t_vec2){x, y}, s);
                flashlight(sh, ray, (t_vec2){x, y + 1}, s);
            }

            y += 2;
        }
    }
}

/*
void	draw_walls(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh;
	t_shaders	*wl;
	int			y;
	__uint32_t	c;
	__uint32_t	s;

	sh = get_img("framework");
	wl = get_walls_texture(ray);
	if (sh && wl)
	{
		y = ray->draw_start;
		while (y < ray->draw_end)
		{
			s = *(__uint32_t *)(wl->img.addr + get_px_adr(&wl->img, (t_vec2){x, y}));
			c = get_shadow(s, (ray->pwall_dist / 15)
					* getvar(VAR_SHADOWS));
			set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), c);
			set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y + 1}), c);
			if (p->flashlight == 1)
			{
				flashlight(sh, ray, (t_vec2){x, y}, s);
				flashlight(sh, ray, (t_vec2){x, y + 1}, s);
			}
			y += 2;
		}
	}
}

void	draw_walls(int x, t_ray *ray, t_player *p)
{
int	pos;
int step;
t_shaders	*wl;
t_shaders	*sh;
int			y;
(void)p;
y = ray->draw_start;
sh = get_img("framework");
wl = get_walls_texture(ray);
t_vec2	u = {(int)(ray->wall_x * (double)wl->img.width), 0};
step = 1.0 * sh->img.height / ray->line_height;
if (ray->side == 0 && ray->dir.x > 0)
	u.x = wl->img.width - u.x - 1;
if (ray->side == 1 && ray->dir.y < 0)
	u.x = wl->img.width - u.x - 1;
pos = (ray->draw_start - 720 + ray->line_height / 2) * step;
while (++y <= ray->draw_end)
	{
		u.y = (int)pos &
			(wl->img.height - 1);
		pos += step;
		if (y < 720 && x < 1280)
		{
			sh->img.addr[y * sh->img.len / 4 + x] = sh->img.addr[u.y * wl->img.len / 4 + u.x];
		}
	}
}

void	ft_draw_texture(t_recup *recup, int x, int y)
{
	y = recup->ray.drawstart - 1;
	ft_init_texture(recup);
	recup->t.step = 1.0 * recup->texture[0].height / recup->ray.lineheight;
	recup->t.texx = (int)(recup->t.wallx * (double)recup->texture
			[recup->t.texdir].width);
	if (recup->ray.side == 0 && recup->ray.raydirx > 0)
		recup->t.texx = recup->texture[recup->t.texdir].width -
			recup->t.texx - 1;
	if (recup->ray.side == 1 && recup->ray.raydiry < 0)
		recup->t.texx = recup->texture[recup->t.texdir].width -
			recup->t.texx - 1;
	recup->t.texpos = (recup->ray.drawstart - recup->ry / 2 +
			recup->ray.lineheight / 2) * recup->t.step;
	while (++y <= recup->ray.drawend)
	{
		recup->t.texy = (int)recup->t.texpos &
			(recup->texture[recup->t.texdir].height - 1);
		recup->t.texpos += recup->t.step;
		if (y < recup->ry && x < recup->rx)
			recup->data.addr[y * recup->data.line_length / 4 + x] =
				recup->texture[recup->t.texdir].addr[recup->t.texy *
					recup->texture[recup->t.texdir].line_length /
					4 + recup->t.texx];
	}
}
*/