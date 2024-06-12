/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:47:32 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/12 08:31:17 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	minimap_rescale(t_mm *mm, t_map *mp)
{
	mm->width = (mm->dimension * mp->width);
	mm->height = (mm->dimension * mp->height);
}

static void	minimap_scaling(t_mm *mm, t_map *mp)
{
	minimap_rescale(mm, mp);
	while (mm->width > mm->size || mm->height > mm->size)
	{
		mm->dimension -= 1;
		if (mm->dimension <= mm->min)
		{
			mm->dimension = mm->min;
			minimap_rescale(mm, mp);
			return ;
		}
		minimap_rescale(mm, mp);
	}
}

void	minimap_settings(t_cb *cub)
{
	t_mm	*mm;
	t_map	*mp;

	if (cub)
	{
		mm = &cub->minimap;
		mp = &cub->map_data;
		mm->dimension = mp->dimension;
		mm->origin = (t_vec2){0, 0};
		mm->size = 150;
		mm->min = 8;
		mm->cone_wireframe = 1;
		mm->minimap_wireframe = 0;
		minimap_scaling(mm, mp);
	}
}
