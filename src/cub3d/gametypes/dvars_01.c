/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvars_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:06:16 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/29 00:55:56 by lchiva           ###   ########.fr       */
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
			printf("%i %i %i\n", v, var->ilimit.x, var->ilimit.y);
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
		cub->vars[VAR_G_SPEED]
			= reg_var(VAR_G_SPEED, 0.1, (t_vec2f){0.05f, 0.6f});
		cub->vars[VAR_G_GRAVITY]
			= reg_var(VAR_G_GRAVITY, 1.0, (t_vec2f){0.3f, 2.0f});
		cub->vars[VAR_SHADOWS]
			= reg_var(VAR_SHADOWS, 1.0, (t_vec2f){0.05f, 2.0f});
		cub->vars[VAR_FLASHLIGHT_RADIUS]
			= reg_var(VAR_FLASHLIGHT_RADIUS, 65.0, (t_vec2f){60.0f, 100.0f});
		cub->vars[VAR_GUN_X]
			= reg_var(VAR_GUN_X, 1.0, (t_vec2f){0.90f, 1.10f});
		cub->vars[VAR_GUN_Y]
			= reg_var(VAR_GUN_Y, 1.1, (t_vec2f){0.88f, 1.60f});
		cub->vars[VAR_FPS]
			= reg_var(VAR_FPS, 16666.0, (t_vec2f){33333.0f, 15384.0f});
		cub->vars[VAR_ASPECT]
			= reg_var(VAR_ASPECT, 1.13f, (t_vec2f){0.60f, 1.85f});
	}
}
