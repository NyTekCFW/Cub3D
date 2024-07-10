/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:39:53 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/08 21:40:03 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	start_hook(void)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		mlx_hook(lx->win, KeyPress, (1L << 0), hook_keyboard_p, lx);
		mlx_hook(lx->win, KeyRelease, (1L << 1), hook_keyboard_r, lx);
	}
}
