/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvars_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:06:16 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/24 20:38:03 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	setdvarint(int id, int v)
{
	t_cb	*cb;
	t_dvars	*var;

	cb = g_cub(ACT_GET);
	if (cb && id > VAR_ERROR && id < VAR_MAX)
	{
		var = &cb->vars[id];
		if (var)
		{
			if (v >= var->ilimit.x && v <= var->ilimit.y)
			{
				var->dvalue = (double)v;
				var->ivalue = v;
			}
		}
	}
}

t_dvars	*get_dvar(int id)
{
	t_cb	*cb;
	t_dvars	*var;

	cb = g_cub(ACT_GET);
	if (cb && id > VAR_ERROR && id < VAR_MAX)
	{
		var = &cb->vars[id];
		if (var)
			return (var);
	}
	return (NULL);
}

void	init_dvars(t_cb *cub)
{
	if (cub)
	{
		cub->vars[VAR_G_SPEED] = reg_var('f', VAR_G_SPEED, 0.1, (t_vec2f){0.05f, 0.6f});
		cub->vars[VAR_G_GRAVITY] = reg_var('f', VAR_G_GRAVITY, 1.0, (t_vec2f){0.3f, 2.0f});
		cub->vars[VAR_SHADOWS] = reg_var('f', VAR_SHADOWS, 1.0, (t_vec2f){0.05f, 2.0f});
		cub->vars[VAR_TIMESCALE] = reg_var('f', VAR_TIMESCALE, 1.0, (t_vec2f){0.05f, 2.0f});
		cub->vars[VAR_FLASHLIGHT_RADIUS] = reg_var('f', VAR_FLASHLIGHT_RADIUS, 85.0, (t_vec2f){15.0f, 135.0f});
	}
}
