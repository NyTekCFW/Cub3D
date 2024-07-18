/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_command_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:44:52 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 16:01:38 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	pflash_light(void)
{
	t_cb	*cub;
	t_key	*key;

	cub = g_cub(ACT_GET);
	key = get_key(BUTTON_FLASHLIGHT);
	if (cub && key)
	{
		cub->player.flashlight = !cub->player.flashlight;
		key->ignore = 1;
		key->is_pressed = 0;
	}
}

static void	pweapfire(void)
{
	t_key	*key;
	t_cb	*cub;
	int		id;

	cub = g_cub(ACT_GET);
	key = get_key(BUTTON_FIRE);
	if (cub && key)
	{
		weapon_fired();
		if (cub->player.weapon)
		{
			id = cub->player.weapon->id;
			if (cub->weapons[id].fire_mode
				== WPN_MODE_SINGLE_SHOT)
			{
				key->ignore = 1;
				key->is_pressed = 0;
			}
		}
	}
}

static void	_p_reg_commands(__uint16_t tab[])
{
	add_keycode(tab[BUTTON_MOVE_FORWARD], pmove_forward);
	add_keycode(tab[BUTTON_MOVE_BACKWARD], pmove_backward);
	add_keycode(tab[BUTTON_LOOK_LEFT], plook_left);
	add_keycode(tab[BUTTON_LOOK_RIGHT], plook_right);
	add_keycode(tab[BUTTON_LOOK_UP], plook_up);
	add_keycode(tab[BUTTON_LOOK_DOWN], plook_down);
	add_keycode(tab[BUTTON_FLASHLIGHT], pflash_light);
	add_keycode(tab[BUTTON_RELOAD], weapon_reload);
	add_keycode(tab[BUTTON_FIRE], pweapfire);
	add_keycode(tab[BUTTON_SWITCH], pswitchweapon);
	add_keycode(tab[BUTTON_SWITCH2], pswitchweapon);
	add_keycode(tab[BUTTON_SPRINT], NULL);
	add_keycode(tab[BUTTON_JUMP], NULL);
	add_keycode(tab[BUTTON_STANCE], NULL);
	add_keycode(tab[BUTTON_INTERACT], NULL);
}

void	p_reg_commands(void)
{
	__uint16_t	*button;

	button = get_buttons();
	if (button)
	{
		button[BUTTON_MOVE_FORWARD] = XK_w;
		button[BUTTON_MOVE_BACKWARD] = XK_s;
		button[BUTTON_LOOK_LEFT] = XK_a;
		button[BUTTON_LOOK_RIGHT] = XK_d;
		button[BUTTON_LOOK_DOWN] = XK_h;
		button[BUTTON_LOOK_UP] = XK_y;
		button[BUTTON_SPRINT] = XK_Shift_L;
		button[BUTTON_JUMP] = XK_space;
		button[BUTTON_FLASHLIGHT] = XK_q;
		button[BUTTON_FIRE] = XK_e;
		button[BUTTON_STANCE] = XK_c;
		button[BUTTON_INTERACT] = XK_f;
		button[BUTTON_FIRE] = XK_MOUSE_LEFT_CLICK;
		button[BUTTON_RELOAD] = XK_r;
		button[BUTTON_SWITCH] = XK_MOUSE_SCROLL_DOWN;
		button[BUTTON_SWITCH2] = XK_MOUSE_SCROLL_UP;
		_p_reg_commands(button);
	}
}
