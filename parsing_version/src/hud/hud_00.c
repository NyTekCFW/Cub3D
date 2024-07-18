/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:37:53 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 16:06:48 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	ml_savemesh(&p, "framework");
	ml_overwrite(&p, 0);
	ml_end(&p);
	p = ml_begin(ML_PRIM_QUADS);
	ml_vertex(&p, (t_vec2){ar->a1.x + 2, ar->a4.y - 204});
	ml_vertex(&p, (t_vec2){ar->a1.x + 10 + x->health, ar->a4.y - 204});
	ml_vertex(&p, (t_vec2){ar->a1.x + 10 + x->health, ar->a4.y - 199});
	ml_vertex(&p, (t_vec2){ar->a1.x + 2, ar->a4.y - 199});
	ml_color(&p, 0xFFFFFF);
	ml_savemesh(&p, "framework");
	ml_overwrite(&p, 0);
	ml_end(&p);
}

static void	score_hud(t_cb *cub, t_shaders *sh)
{
	t_shaders	*fr;
	t_area		*ar;

	fr = get_img("/hud_score.xpm");
	if (cub && fr && sh)
	{
		ar = &cub->screen.area;
		merge_img(sh, fr, (t_vec2){ar->a1.x, ar->a4.y - 194});
		typewritter("framework", "$500999", (t_vec2){ar->a1.x + 2, ar->a4.y - 192});
	}
}

static void	weapon_hud(t_cb *cub, t_shaders *sh)
{
	t_area	*ar;

	ar = &cub->screen.area;
	merge_img(sh, get_img("/dpad_bar.xpm"),
		(t_vec2){ar->a3.x - 306, ar->a3.y - 116});
	merge_img(sh, get_img("/dpad.xpm"),
		(t_vec2){ar->a3.x - 110, ar->a3.y - 205});
	get_weapon_info();
	typewritter("framework", cub->player.weapon->info_buffer,
		(t_vec2){ar->a3.x - 200, ar->a3.y - 168});
}

static void	crosshair_hud(t_cb *cub, t_shaders *sh)
{
	t_shaders	*cv;
	t_shaders	*ch;
	int			v;

	if (cub)
	{
		cv = get_img("/crosshair_v.xpm");
		ch = get_img("/crosshair_h.xpm");
		v = (cub->player.velocity * 8);
		if (ch && cv && sh)
		{
			merge_img(sh, cv, (t_vec2){638, 347 - v});
			merge_img(sh, cv, (t_vec2){638, 363 + v});
			merge_img(sh, ch, (t_vec2){627 - v, 358});
			merge_img(sh, ch, (t_vec2){643 + v, 358});
		}
	}
}

void	hud_render(void)
{
	t_cb		*cub;
	t_shaders	*sh;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		sh = cub->texture[TEX_RENDER];
		if (sh)
		{
			weapon_hud(cub, sh);
			score_hud(cub, sh);
			health_bar(cub);
			crosshair_hud(cub, sh);
		}
	}
}
