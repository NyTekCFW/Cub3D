/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_merge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:08:47 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/25 16:35:54 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

/// @brief merge 2 images at a specific position and set a custom color
/// @param d dest image
/// @param b base image
/// @param u position
void	merge_img(t_shaders *d, t_shaders *b, t_vec2 u)
{
	__uint32_t	co;
	t_vec2		i;

	i = (t_vec2){0, 0};
	if (d && b)
	{
		while (i.y < b->img.height)
		{
			i.x = 0;
			while (i.x < b->img.width)
			{
				if ((u.x + i.x) >= 0 && (u.x + i.x) < d->img.width
					&& (u.y + i.y) >= 0 && (u.y + i.y) < d->img.height)
				{
					co = get_px_color(&b->img, i);
					if (is_valid_color(co))
						set_color(&d->img, get_px_adr(&d->img,
								(t_vec2){u.x + i.x, u.y + i.y}), co);
				}
				i.x++;
			}
			i.y++;
		}
	}
}
