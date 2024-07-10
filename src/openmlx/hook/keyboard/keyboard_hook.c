/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:36:57 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/08 22:10:11 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/openmlx.h"

int	hook_keyboard_r(int ks, void *data)
{
	(void)data;
	if (ks > 0xFFFF)
		return (0);
	set_keynum_status(get_key_num(ks), 0);
	return (1);
}

int	hook_keyboard_p(int ks, void *data)
{
	int	num;

	(void)data;
	if (ks > 0xFFFF)
		return (0);
	num = get_key_num(ks);
	set_keynum_status(num, 1);
	keynum_execute(num);
	return (1);
}
