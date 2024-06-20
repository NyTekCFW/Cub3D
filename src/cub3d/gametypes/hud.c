/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:37:53 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/20 08:50:36 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	health_bar(t_ml *lx, t_cb *cub)
{
	t_prim	p;

	p = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&p, (t_vec2){5, lx->height - 205});
	ml_vertex(&p, (t_vec2){139, lx->height - 205});
	ml_vertex(&p, (t_vec2){139, lx->height - 198});
	ml_vertex(&p, (t_vec2){5, lx->height - 198});
	ml_color(&p, 0x030303);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
	p = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&p, (t_vec2){7, lx->height - 203});
	ml_vertex(&p, (t_vec2){7 + cub->player.health, lx->height - 203});
	ml_vertex(&p, (t_vec2){7 + cub->player.health, lx->height - 200});
	ml_vertex(&p, (t_vec2){7, lx->height - 200});
	ml_color(&p, 0xFFFFFF);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
}

static void	score_hud(t_ml *lx)
{
	t_prim	p;

	p = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&p, (t_vec2){3, lx->height - 194});
	ml_vertex(&p, (t_vec2){141, lx->height - 194});
	ml_vertex(&p, (t_vec2){141, lx->height - 162});
	ml_vertex(&p, (t_vec2){3, lx->height - 162});
	ml_color(&p, 0x7F7F7F);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
	p = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&p, (t_vec2){5, lx->height - 196});
	ml_vertex(&p, (t_vec2){139, lx->height - 196});
	ml_vertex(&p, (t_vec2){139, lx->height - 160});
	ml_vertex(&p, (t_vec2){5, lx->height - 160});
	ml_color(&p, 0x030303);
	ml_savemesh(&p, get_img("framework"));
	ml_end(&p);
	typewritter("$500999", (t_vec2){0, lx->height - 194});
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
		score_hud(lx);
		health_bar(lx, cub);
	}
}
