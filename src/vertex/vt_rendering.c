/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vt_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:33:10 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/05 14:09:30 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

void	ml_draw_points(t_prim *s)
{
	t_vec2		p;
	t_vec2		m[2];
	int			i;

	i = s->size / 2;
	m[0] = (t_vec2){s->point[0].x - i, s->point[0].y - i};
	m[1] = (t_vec2){s->point[0].x + i, s->point[0].y + i};
	p.y = m[0].y;
	while (p.y < m[1].y)
	{
		p.x = m[0].x;
		while (p.x < m[1].x)
		{
			if (ml_can_draw(s, p))
				ml_put_pixel(p.x, p.y, s->color);
			p.x++;
		}
		p.y++;
	}
}

static void	lines_render(t_prim *s, double imz[], t_vec2 p[], double d[])
{
	imz[2] = 0;
	while (imz[2] < imz[1])
	{
		if (ml_can_draw(s, (t_vec2){(p[0].x + imz[2]) + imz[0] * d[0],
				(p[0].y + imz[2]) + imz[0] * d[1]}))
			ml_put_pixel((p[0].x + imz[2]) + imz[0] * d[0], \
			(p[0].y + imz[2]) + imz[0] * d[1], s->color);
		if (ml_can_draw(s, (t_vec2){(p[0].x - imz[2]) + imz[0] * d[0],
				(p[0].y - imz[2]) + imz[0] * d[1]}))
			ml_put_pixel((p[0].x - imz[2]) + imz[0] * d[0], \
			(p[0].y - imz[2]) + imz[0] * d[1], s->color);
		imz[2] += 0.01;
	}
}

void	ml_draw_lines(t_prim *s, int w, int e)
{
	double	d[2];
	t_vec2	p[2];
	double	length;
	double	imz[3];

	xmemcpy(imz, (double []){0.0, s->size / 2, 0.0}, sizeof(imz));
	if (s->size == 1)
		imz[1] = 0;
	p[0] = (t_vec2){s->point[w].x, s->point[w].y};
	p[1] = (t_vec2){s->point[e].x, s->point[e].y};
	d[0] = p[1].x - p[0].x;
	d[1] = p[1].y - p[0].y;
	length = sqrt(d[0] * d[0] + d[1] * d[1]);
	while (imz[0] < 1.0)
	{
		lines_render(s, imz, p, d);
		imz[0] += 1.0 / length;
	}
}

void	ml_draw_line_sl(t_prim *s)
{
	int	i;

	i = 0;
	while (i < s->cpoint)
	{
		if (i + 1 == s->cpoint)
			break ;
		ml_draw_lines(s, i, i + 1);
		i++;
	}
	if (s->primitive != ML_PRIM_LINE_STRIP)
		ml_draw_lines(s, i, 0);
}
