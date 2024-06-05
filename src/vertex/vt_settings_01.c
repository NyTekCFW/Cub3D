/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vt_settings_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:59:33 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/02 12:40:22 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

void	ml_setuv(t_prim *s, int uv)
{
	if (uv < ML_UV_MAX && uv >= ML_UV_0)
		s->uv = uv;
}

void	ml_setwrap(t_prim *s, int wrap)
{
	if (wrap < ML_WRAP_MAX && wrap >= ML_WRAP_REPEAT)
		s->wrapping = wrap;
}

void	ml_setmode(t_prim *s, int mode)
{
	if (mode < ML_MODE_MAX && mode >= ML_MODE_FILL)
		s->mode = mode;
}

void	ml_settexture(t_prim *s, char *name)
{
	t_shaders	*sh;

	sh = get_img(name);
	if (sh)
	{
		s->texture = ML_TEXTURE_IMG;
		s->img = &sh->img;
		s->color_texture = 0xFFFFFF;
		s->intensity = 1.0f;
	}
}

void	ml_setintensity(t_prim *s, float i)
{
	if (i < 0.0f)
		i = 0.0f;
	else if (i > 1.0f)
		i = 1.0f;
	s->intensity = i;
}
