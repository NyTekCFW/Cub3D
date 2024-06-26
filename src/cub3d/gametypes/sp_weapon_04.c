/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_weapon_04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:15:20 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/25 16:21:49 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	walk_loop_anim(t_cb *cub, t_weapon *wpn, t_vec2 *v, size_t len)
{
	t_weapon_data	*data;

	data = &cub->weapons[wpn->id];
	if (v->y == 0 && v->x < data->frame[WPN_FRAME_WALK])
	{
		v->x += 1;
		if (v->x >= data->frame[WPN_FRAME_WALK])
			v->y = 1;
	}
	else if (v->y == 1 && v->x >= 0)
	{
		v->x -= 1;
		if (v->x < 0)
		{
			v->y = 0;
			v->x = 0;
			wpn->anim_buffer[len - 1] = '0';
		}
	}
}

void	run_weapon_anim(void)
{
	static t_vec2	v = {0, 0};
	t_cb			*cub;
	t_weapon		*wpn;
	size_t			len;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		wpn = cub->player.weapon;
		if (wpn)
		{
			xstrcpy(wpn->anim_buffer, cub->weapons[wpn->id].name);
			len = xstrlen(wpn->anim_buffer);
			xstrcpy(wpn->anim_buffer + len, "_walk_000\0");
			len = xstrlen(wpn->anim_buffer);
			wpn->anim_buffer[len - 3] = 0x30 + (v.x / 100);
			wpn->anim_buffer[len - 2] = 0x30 + ((v.x / 10) % 10);
			wpn->anim_buffer[len - 1] = 0x30 + (v.x % 10);
			walk_loop_anim(cub, wpn, &v, len);
		}
	}
}
