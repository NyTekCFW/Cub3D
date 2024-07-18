/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:04:23 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/18 10:57:35 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	g_exit(t_cb *cub)
{
	int	i;

	i = 0;
	if (cub && cub->map_data.file)
	{
		xfree((void **)&cub->map_data.file->content);
		while (i < 6)
		{
			xfree((void **)&cub->map_data.texture[i]);
			i++;
		}	
		i = 0;
		while (i < cub->map_data.file->total_line)
		{
			xfree((void **)&cub->map_data.file->map[i]);
			i++;
		}
		xfree((void **)&cub->map_data.file->map);
		cub->map_data.file->pos = NULL;
		xfree((void **)&cub->map_data.file);
	}
	g_cub(ACT_FREE);
}

t_cb	*g_cub(int act)
{
	static t_cb	*cub;

	if (act == ACT_INIT && xalloc((void **)&cub, 1, sizeof(t_cb)))
	{
		initial_center_screen(cub);
		init_dvars(cub);
		xalloc((void **)&cub->map_data.file, sizeof(t_file), 1);
		return (cub);
	}
	else if (act == ACT_GET && cub)
		return (cub);
	else if (act == ACT_FREE && cub)
		return (xfree((void **)&cub), NULL);
	return (NULL);
}
