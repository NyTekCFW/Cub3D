/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:42:59 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/25 23:26:50 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	cross_top(t_cb *cub)
{
	t_prim		p;

	p = ml_begin(ML_PRIM_LINES);
	ml_vertex(&p, (t_vec2){640, 348 - (cub->player.velocity * 8)});
	ml_vertex(&p, (t_vec2){640, 358 - (cub->player.velocity * 8)});
	ml_size(&p, 4);
	ml_color(&p, 0x030303);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
	p = ml_begin(ML_PRIM_LINES);
	ml_vertex(&p, (t_vec2){640, 350 - (cub->player.velocity * 8)});
	ml_vertex(&p, (t_vec2){640, 356 - (cub->player.velocity * 8)});
	ml_size(&p, 2);
	ml_color(&p, 0xFFFFFF);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
}

static void	cross_down(t_cb *cub)
{
	t_prim		p;

	p = ml_begin(ML_PRIM_LINES);
	ml_vertex(&p, (t_vec2){640, 362 + (cub->player.velocity * 8)});
	ml_vertex(&p, (t_vec2){640, 372 + (cub->player.velocity * 8)});
	ml_size(&p, 4);
	ml_color(&p, 0x030303);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
	p = ml_begin(ML_PRIM_LINES);
	ml_vertex(&p, (t_vec2){640, 370 + (cub->player.velocity * 8)});
	ml_vertex(&p, (t_vec2){640, 364 + (cub->player.velocity * 8)});
	ml_size(&p, 2);
	ml_color(&p, 0xFFFFFF);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
}

static void	cross_left(t_cb *cub)
{
	t_prim		p;

	p = ml_begin(ML_PRIM_LINES);
	ml_vertex(&p, (t_vec2){628 - (cub->player.velocity * 8), 360});
	ml_vertex(&p, (t_vec2){638 - (cub->player.velocity * 8), 360});
	ml_size(&p, 4);
	ml_color(&p, 0x030303);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
	p = ml_begin(ML_PRIM_LINES);
	ml_vertex(&p, (t_vec2){630 - (cub->player.velocity * 8), 360});
	ml_vertex(&p, (t_vec2){636 - (cub->player.velocity * 8), 360});
	ml_size(&p, 2);
	ml_color(&p, 0xFFFFFF);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
}

static void	cross_right(t_cb *cub)
{
	t_prim		p;

	p = ml_begin(ML_PRIM_LINES);
	ml_vertex(&p, (t_vec2){642 + (cub->player.velocity * 8), 360});
	ml_vertex(&p, (t_vec2){652 + (cub->player.velocity * 8), 360});
	ml_size(&p, 4);
	ml_color(&p, 0x030303);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
	p = ml_begin(ML_PRIM_LINES);
	ml_vertex(&p, (t_vec2){650 + (cub->player.velocity * 8), 360});
	ml_vertex(&p, (t_vec2){644 + (cub->player.velocity * 8), 360});
	ml_size(&p, 2);
	ml_color(&p, 0xFFFFFF);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
}

void	crosshair_hud(t_cb *cub)
{
	cross_top(cub);
	cross_down(cub);
	cross_left(cub);
	cross_right(cub);
}
