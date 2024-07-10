/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:58:58 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/08 21:09:18 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/openmlx.h"

/// @brief get the keycode number in list
/// @param code e.g: XK_w, XK_a ....
/// @return -1 = not found -2 error
/// else is the num of the keycode
int	get_key_num(__uint16_t code)
{
	int		i;
	t_ml	*lx;

	i = 0;
	lx = gmlx(ACT_GET);
	if (lx)
	{
		while (i < 256)
		{
			if (lx->key[i].code == 0)
				break ;
			if (lx->key[i].code == code)
				return (i);
			i++;
		}
		if (i >= 256)
			return (xwrite(1, "Out of key list\n", 16), -2);
		else
			return (-1);
	}
	xwrite(1, "Error : gmlx is null\n", 19);
	return (-2);
}

/// @brief replace the current callback function
/// @param code e.g: XK_w, XK_a ....
/// @param func function that will
///replace the current callback
///function
void	keycode_replace(__uint16_t code, void (*(func))())
{
	int		i;
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	i = get_key_num(code);
	if (i == -1)
	{
		xwrite(1, "Error : Key code not registered!\n", 33);
		return ;
	}
	if (lx && i >= 0 && i < 256)
		lx->key[i].callback = func;
}

/// @brief Call this function to set
/// if the keycode is pressed or not
/// @param code e.g: XK_w, XK_a ....
/// @param active 1 = true 0 = false 
void	set_keycode_status(__uint16_t code, __uint8_t active)
{
	int		i;
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	i = get_key_num(code);
	if (lx && i >= 0 && i < 256)
		lx->key[i].is_pressed = active;
}

/// @brief return 1 if the keycode is pressed
/// @param code e.g: XK_w, XK_a ....
/// @return 
int	keycode_is_pressed(__uint16_t code)
{
	t_ml	*lx;
	int		i;

	lx = gmlx(ACT_GET);
	i = get_key_num(code);
	if (lx && i >= 0 && i < 256)
		return (lx->key[i].is_pressed);
	return (0);
}

/// @brief check if the keycode is pressed
///and execute the func attribued if the
///func is not null
/// @param code e.g : XK_w, XK_a ....
/// @return 
int	keycode_execute(__uint16_t code)
{
	t_ml	*lx;
	int		i;

	lx = gmlx(ACT_GET);
	i = get_key_num(code);
	if (lx && i >= 0 && i < 256)
	{
		if (keycode_is_pressed(code) && lx->key[i].callback != NULL)
		{
			lx->key[i].callback();
			return (1);
		}
	}
	return (0);
}
