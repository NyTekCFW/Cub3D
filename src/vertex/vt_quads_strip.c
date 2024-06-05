/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vt_quads_strip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:45:18 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/02 10:15:17 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

void	ml_draw_quad_strip(t_prim *s)
{
	int		i;
	t_prim	quad;

	i = 0;
	while (i < s->cpoint - 3)
	{
		quad = ml_begin(ML_PRIM_QUADS);
		ml_vertex(&quad, s->point[i]);
		ml_vertex(&quad, s->point[i + 1]);
		ml_vertex(&quad, s->point[i + 2]);
		ml_vertex(&quad, s->point[i + 3]);
		ml_color(&quad, s->color);
		ml_setmode(&quad, s->mode);
		ml_size(&quad, s->size);
		if (s->texture != ML_TEXTURE_NONE)
		{
			quad.texture = s->texture;
			quad.img = s->img;
			quad.color_texture = s->color_texture;
			quad.intensity = s->intensity;
		}
		ml_end(&quad);
		i += 2;
	}
}
