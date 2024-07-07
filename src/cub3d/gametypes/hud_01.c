/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:42:59 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/07 23:36:46 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	crosshair_hud(t_cb *cub, t_shaders *sh)
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
