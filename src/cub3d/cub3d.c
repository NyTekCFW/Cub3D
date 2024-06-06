/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:06:33 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/06 06:21:19 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	minimap_scaling(t_mm *mm)
{
	while (mm->width > mm->size || mm->height > mm->size)
	{
		mm->dimension -= 1;
		if (mm->dimension < mm->min)
		{
			mm->dimension = mm->min;
			while (mm->width > mm->size || mm->height > mm->size)
			{
				mm->scale -= 0.1f;
				if (mm->scale < 0.3f)
				{
					mm->scale = 0.3f;
					return ;
				}
				mm->width = mm->dimension * 9 * mm->scale;
				mm->height = mm->dimension * 9 * mm->scale;
			}
		}
		mm->width = mm->dimension * 9 * mm->scale;
		mm->height = mm->dimension * 9 * mm->scale;
	}
}

static void	minimap_init(t_cb *cub)
{
	t_mm	*mm;

	mm = &cub->minimap;
	mm->origin = (t_vec2){0, 0};
	mm->scale = 1.0f;
	mm->size = 120;
	mm->min = 15;
	mm->dimension = 60;
	mm->view_filled = 0;
	mm->width = mm->dimension * 9 * mm->scale;
	mm->height = mm->dimension * 9 * mm->scale;
	minimap_scaling(mm);
}

t_cb	*g_cub(int act)
{
	static t_cb	*cub;

	if (act == ACT_INIT && xalloc((void **)&cub, 1, sizeof(t_cb)))
	{
		minimap_init(cub);
		return (cub);
	}
	else if (act == ACT_GET && cub)
		return (cub);
	else if (act == ACT_FREE && cub)
		return (xfree((void **)&cub), NULL);
	return (NULL);
}
