/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:37:53 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/25 23:35:34 by lchiva           ###   ########.fr       */
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
	ml_overwrite(&p, 0);
	ml_end(&p);
	p = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&p, (t_vec2){ar->a1.x + 1, ar->a4.y - 204});
	ml_vertex(&p, (t_vec2){ar->a1.x + 10 + x->health, ar->a4.y - 204});
	ml_vertex(&p, (t_vec2){ar->a1.x + 10 + x->health, ar->a4.y - 199});
	ml_vertex(&p, (t_vec2){ar->a1.x + 1, ar->a4.y - 199});
	ml_color(&p, 0xFFFFFF);
	ml_savemesh(&p, get_img("framework"));
	ml_overwrite(&p, 0);
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
	ml_overwrite(&p, 0);
	ml_end(&p);
	p = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&p, (t_vec2){ar->a1.x + 1, ar->a4.y - 193});
	ml_vertex(&p, (t_vec2){ar->a1.x + 140, ar->a4.y - 193});
	ml_vertex(&p, (t_vec2){ar->a1.x + 140, ar->a4.y - 159});
	ml_vertex(&p, (t_vec2){ar->a1.x + 1, ar->a4.y - 159});
	ml_color(&p, 0x030303);
	ml_savemesh(&p, get_img("framework"));
	ml_overwrite(&p, 0);
	ml_end(&p);
	typewritter("$500999", (t_vec2){ar->a1.x + 2, ar->a4.y - 194});
}

static void	weapon_hud(t_cb *cub)
{
	t_prim	p;
	t_area	*ar;

	ar = &cub->screen.area;
	p = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&p, (t_vec2){ar->a3.x - 306, ar->a3.y - 116});
	ml_vertex(&p, (t_vec2){ar->a3.x - 50, ar->a3.y - 116});
	ml_vertex(&p, (t_vec2){ar->a3.x - 50, ar->a3.y - 100});
	ml_vertex(&p, (t_vec2){ar->a3.x - 306, ar->a3.y - 100});
	ml_savemesh(&p, get_img("framework"));
	ml_settexture(&p, "/dpad_bar.xpm");
	ml_setwrap(&p, ML_WRAP_REPEAT_CENTER);
	ml_overwrite(&p, 0);
	ml_end(&p);
	p = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&p, (t_vec2){ar->a3.x - 110, ar->a3.y - 205});
	ml_vertex(&p, (t_vec2){ar->a3.x + 18, ar->a3.y - 205});
	ml_vertex(&p, (t_vec2){ar->a3.x + 18, ar->a3.y - 77});
	ml_vertex(&p, (t_vec2){ar->a3.x - 110, ar->a3.y - 77});
	ml_savemesh(&p, get_img("framework"));
	ml_settexture(&p, "/dpad.xpm");
	ml_setwrap(&p, ML_WRAP_REPEAT_CENTER);
	ml_overwrite(&p, 0);
	ml_end(&p);
	get_weapon_info();
	typewritter(cub->player.weapon->info_buffer,
		(t_vec2){ar->a3.x - 200, ar->a3.y - 168});
}

void	hud_render(void)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		weapon_hud(cub);
		score_hud(cub);
		health_bar(cub);
		crosshair_hud(cub);
	}
}
