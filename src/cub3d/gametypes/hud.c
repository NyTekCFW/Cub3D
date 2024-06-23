/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:37:53 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/21 16:59:08 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	health_bar(t_cb *cub)
{
	t_prim		p;
	t_area		*ar;
	t_player	*x;

	ar = &cub->screen.area;
	x = &cub->player;
	p = ml_begin(ML_PRIM_LINE_LOOP);
	ml_vertex(&p, (t_vec2){ar->a1.x, ar->a4.y - 205});
	ml_vertex(&p, (t_vec2){ar->a1.x + 142, ar->a4.y - 205});
	ml_vertex(&p, (t_vec2){ar->a1.x + 142, ar->a4.y - 198});
	ml_vertex(&p, (t_vec2){ar->a1.x, ar->a4.y - 198});
	ml_color(&p, 0x030303);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
	p = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&p, (t_vec2){ar->a1.x + 1, ar->a4.y - 204});
	ml_vertex(&p, (t_vec2){ar->a1.x + 10 + x->health, ar->a4.y - 204});
	ml_vertex(&p, (t_vec2){ar->a1.x + 10 + x->health, ar->a4.y - 199});
	ml_vertex(&p, (t_vec2){ar->a1.x + 1, ar->a4.y - 199});
	ml_color(&p, 0xFFFFFF);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
}

static void	score_hud(t_cb *cub)
{
	t_prim	p;
	t_area	*ar;

	p = ml_begin(ML_PRIM_LINE_LOOP);
	ar = &cub->screen.area;
	ml_vertex(&p, (t_vec2){ar->a1.x, ar->a4.y - 194});
	ml_vertex(&p, (t_vec2){ar->a1.x + 142, ar->a4.y - 194});
	ml_vertex(&p, (t_vec2){ar->a1.x + 142, ar->a4.y - 158});
	ml_vertex(&p, (t_vec2){ar->a1.x, ar->a4.y - 158});
	ml_color(&p, 0xFFFFFF);
	ml_size(&p, 2);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
	p = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&p, (t_vec2){ar->a1.x + 1, ar->a4.y - 193});
	ml_vertex(&p, (t_vec2){ar->a1.x + 140, ar->a4.y - 193});
	ml_vertex(&p, (t_vec2){ar->a1.x + 140, ar->a4.y - 159});
	ml_vertex(&p, (t_vec2){ar->a1.x + 1, ar->a4.y - 159});
	ml_color(&p, 0x030303);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
	typewritter("$500999", (t_vec2){ar->a1.x + 2, ar->a4.y - 194});
}

static void	weapon_hud(t_ml *lx, t_cb *cub)
{
	t_prim			p;

	p = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&p, (t_vec2){lx->width - 140, lx->height - 205});
	ml_vertex(&p, (t_vec2){lx->width - 0, lx->height - 205});
	ml_vertex(&p, (t_vec2){lx->width - 0, lx->height - 140});
	ml_vertex(&p, (t_vec2){lx->width - 140, lx->height - 140});
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
	get_weapon_info();
	typewritter(cub->player.weapon->info_buffer,
		(t_vec2){lx->width - 120, lx->height - 200});
}

void	hud_render(void)
{
	t_ml	*lx;
	t_cb	*cub;

	lx = gmlx(ACT_GET);
	cub = g_cub(ACT_GET);
	if (lx && cub)
	{
		weapon_hud(lx, cub);
		score_hud(cub);
		health_bar(cub);
	}
}
