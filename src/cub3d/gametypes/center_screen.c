/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:03:39 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/25 23:35:50 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	draw_safe_area(void)
{
	t_cb		*cub;
	t_prim		s;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		s = ml_begin(ML_PRIM_QUADS);
		ml_vertex(&s, cub->screen.area.a1);
		ml_vertex(&s, cub->screen.area.a2);
		ml_vertex(&s, cub->screen.area.a3);
		ml_vertex(&s, cub->screen.area.a4);
		ml_color(&s, 0xff0000);
		ml_setmode(&s, ML_MODE_LINE);
		ml_savemesh(&s, get_img("framework"));
		ml_overwrite(&s, 0);
		ml_end(&s);
	}
}

void	safe_area_update(t_screen *sc)
{
	t_vec2	v;

	if (sc)
	{
		v = (t_vec2){1280 - (sc->x + 20), 720 - (sc->y + 20)};
		sc->area.a1 = (t_vec2){20 - sc->area.u.x, 20 - sc->area.u.y};
		sc->area.a2 = (t_vec2)
		{
			sc->x + v.x + sc->area.u.x,
			20 - sc->area.u.y
		};
		sc->area.a3 = (t_vec2)
		{
			sc->x + v.x + sc->area.u.x,
			sc->y + v.y + sc->area.u.y
		};
		sc->area.a4 = (t_vec2)
		{
			20 - sc->area.u.x,
			sc->y + v.y + sc->area.u.y
		};
	}
}

void	initial_center_screen(t_cb *cub)
{
	t_vec2	diff;
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx && cub)
	{
		if (lx->width == 1280 && lx->height == 720)
		{
			cub->screen.x = 0;
			cub->screen.y = 0;
		}
		else
		{
			diff = (t_vec2)
			{
				(lx->width - 1280),
				(lx->height - 720)
			};
			cub->screen.x = diff.x - (diff.x / 2);
			cub->screen.y = diff.y - (diff.y / 2);
		}
		cub->screen.area.u = (t_vec2){0, 0};
		safe_area_update(&cub->screen);
	}
}
