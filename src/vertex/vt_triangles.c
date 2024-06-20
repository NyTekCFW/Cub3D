/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vt_triangles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:09:48 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/07 18:06:59 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

static void	ml_draw_triangles_rendering(t_prim *s, int xinter[], t_vec4 *ijt)
{
	ijt->y = xinter[ijt->x];
	while (ijt->y <= xinter[ijt->x + 1])
	{
		if (ml_can_draw(s, (t_vec2){ijt->y, ijt->w}))
		{
			if (s->savemesh)
				set_color(s->savemesh, get_px_adr(s->savemesh,
						(t_vec2){ijt->y, ijt->w}), s->color);
			else
				ml_put_pixel(ijt->y, ijt->w, s->color);
		}
		ijt->y++;
	}
}

static void	ml_draw_triangles_inter(t_prim *s, int *inter, int xinter[], int y)
{
	t_vec4	ijt;

	ijt = (t_vec4){0, 1, 0, y};
	while (ijt.x < *inter - 1)
	{
		ijt.y = ijt.x + 1;
		while (ijt.y < *inter)
		{
			if (xinter[ijt.x] > xinter[ijt.y])
			{
				ijt.z = xinter[ijt.x];
				xinter[ijt.x] = xinter[ijt.y];
				xinter[ijt.y] = ijt.z;
			}
			ijt.y++;
		}
		ijt.x++;
	}
	ijt = (t_vec4){0, 0, 0, y};
	while (ijt.x < *inter)
	{
		ml_draw_triangles_rendering(s, xinter, &ijt);
		ijt.x += *inter;
	}
}

static void	ml_draw_triangles_calc(t_prim *s, int *inter, int y)
{
	int		i;
	t_vec3	j;
	int		xinter[3];

	i = 0;
	while (i < 3)
	{
		j.x = (i + 1) % 3;
		j.y = s->point[i].y;
		j.z = s->point[j.x].y;
		if ((j.y <= y && j.z > y) || (j.z <= y && j.y > y))
		{
			if (j.z - j.y != 0)
			{
				xinter[*inter] = s->point[i].x + (s->point[j.x].x \
				- s->point[i].x) * (y - j.y) / (j.z - j.y);
				(*inter)++;
			}
		}
		i++;
	}
	ml_draw_triangles_inter(s, inter, xinter, y);
}

void	ml_draw_triangles(t_prim *s)
{
	int		i;
	int		y;
	t_vec2	mm;
	int		inter;

	if (s->mode != ML_MODE_FILL)
		return (ml_draw_line_sl(s), (void)0);
	i = 1;
	mm = (t_vec2){s->point[0].y, s->point[0].y};
	while (i < 3)
	{
		if (s->point[i].y < mm.x)
			mm.x = s->point[i].y;
		if (s->point[i].y > mm.y)
			mm.y = s->point[i].y;
		i++;
	}
	y = mm.x;
	while (y <= mm.y)
	{
		inter = 0;
		ml_draw_triangles_calc(s, &inter, y);
		y++;
	}
}
