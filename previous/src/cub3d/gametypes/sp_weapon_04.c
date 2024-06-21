/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_weapon_04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:15:20 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/17 17:36:35 by lchiva           ###   ########.fr       */
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
	usleep(8000);
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
/*
void	run_weapon_anim(void)
{
	static int	v = 0;
	static int	b = 0;
	t_cb		*cub;
	t_weapon	*wpn;
	char		buffer[64];
	size_t		len;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		wpn = cub->player.weapon;
		if (wpn)
		{
			xmemset(buffer, 0, 64);
			xstrcpy(wpn->anim_buffer, cub->weapons[wpn->id].name);
			xstrcpy(wpn->anim_buffer + xstrlen(cub->weapons[wpn->id].name), "_walk_000\0");
			len = xstrlen(wpn->anim_buffer);
			wpn->anim_buffer[len - 3] = 0x30 + (b / 100);
			wpn->anim_buffer[len - 2] = 0x30 + ((b / 10) % 10);
			wpn->anim_buffer[len - 1] = 0x30 + (b % 10);
			//wpn->anim_frame++;
			//wpn->anim_frame++;
			if (v == 0 && b < cub->weapons[wpn->id].frame[WPN_FRAME_WALK])
			{
				b++;
				usleep(8000);
				return ;
			}
			v = 1;
			if (v == 1 && b >= 0)
			{
				b--;
				usleep(8000);
				return ;
			}
			v = 0;
			b = 0;
			wpn->anim_buffer[len - 1] = '0';
			printf("%s\n", wpn->anim_buffer);
		}
	}
}
*/