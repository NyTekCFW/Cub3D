/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:06:33 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/09 15:04:43 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


t_cb	*g_cub(int act)
{
	static t_cb	*cub;

	if (act == ACT_INIT && xalloc((void **)&cub, 1, sizeof(t_cb)))
	{
		map_init(cub);
		minimap_settings(cub);
		player_settings(cub);
		return (cub);
	}
	else if (act == ACT_GET && cub)
		return (cub);
	else if (act == ACT_FREE && cub)
		return (xfree((void **)&cub), NULL);
	return (NULL);
}
