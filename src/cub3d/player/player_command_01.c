/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_command_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:44:52 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/08 22:26:26 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	pflash_light(void)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (cub)
		cub->player.flashlight = !cub->player.flashlight;
}

void	psprint(void)
{
	setdvar(VAR_G_SPEED, 0.17);
}

void	p_reg_commands(void)
{
	add_keycode(XK_w, pmove_forward);
	add_keycode(XK_s, pmove_backward);
	add_keycode(XK_a, plook_left);
	add_keycode(XK_d, plook_right);
	add_keycode(XK_q, pflash_light);
	add_keycode(XK_Shift_L, psprint);
	add_keycode(XK_r, weapon_reload);
	add_keycode(XK_e, weapon_fired);
}
