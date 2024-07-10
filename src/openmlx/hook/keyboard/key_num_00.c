/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_num_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:39:44 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/08 21:09:07 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/openmlx.h"

/// @brief replace the current callback function
/// @param num obtained via get_key_num(code)
/// @param func function that will
///replace the current callback
///function
void	keynum_replace(int num, void (*(func))())
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (num == -1)
	{
		xwrite(1, "Error : Key num not registered!\n", 32);
		return ;
	}
	if (lx && num >= 0 && num < 256)
		lx->key[num].callback = func;
}

/// @brief Call this function to set
/// if the keynum is pressed or not
/// @param num obtained via get_key_num(code)
/// @param active 1 = true 0 = false 
void	set_keynum_status(int num, __uint8_t active)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx && num >= 0 && num < 256)
		lx->key[num].is_pressed = active;
}

/// @brief return 1 if the keynum is pressed
/// @param code num obtained via get_key_num(code)
/// @return 
int	keynum_is_pressed(int num)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx && num >= 0 && num < 256)
		return (lx->key[num].is_pressed);
	return (0);
}

/// @brief check if the keynum is pressed
///and execute the func attribued if the
///func is not null
/// @param code num obtained via get_key_num(code)
/// @return 
int	keynum_execute(int num)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx && num >= 0 && num < 256)
	{
		if (keynum_is_pressed(num) && lx->key[num].callback != NULL)
		{
			lx->key[num].callback();
			return (1);
		}
	}
	return (0);
}
