/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_mouse_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:42:07 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 12:16:44 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief mouse button pressed handler
/// @param ks mouse button code
/// @param x x position in window
/// @param y y position in window
/// @param data ptr to handle
int	hook_mouse_p(int ks, int x, int y, t_ml *lx)
{
	if (lx && !lx->quit)
	{
		(void)x;
		(void)y;
		if (ks > 0xFFFF)
			return (0);
		set_keycode_status(ks, 1);
		if (ks == XK_MOUSE_SCROLL_DOWN
			|| ks == XK_MOUSE_SCROLL_UP)
			keynum_execute(get_key_num(ks));
	}
	return (1);
}

/// @brief mouse button release handler
/// @param ks mouse button code
/// @param x x position in window
/// @param y y position in window
/// @param data ptr to handle
int	hook_mouse_r(int ks, int x, int y, t_ml *lx)
{
	if (lx && !lx->quit)
	{
		(void)x;
		(void)y;
		if (ks > 0xFFFF)
			return (0);
		set_keycode_status(ks, 0);
	}
	return (1);
}

/// @brief mouse motion handler
/// @param x x position in window
/// @param y y position in window
/// @param data ptr to handle
int	hook_mouse_m(int x, int y, t_ml *lx)
{
	if (lx && !lx->quit)
	{
		(void)x;
		(void)y;
	}
	return (1);
}
