/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:34:11 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/08 22:50:06 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	_g_exit(void)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		keynum_replace(i, NULL);
		i++;
	}
}

t_cb	*g_cub(int act)
{
	static t_cb	*cub;

	if (act == ACT_INIT && xalloc((void **)&cub, 1, sizeof(t_cb)))
	{
		initial_center_screen(cub);
		initial_weapons_data(cub);
		init_dvars(cub);
		map_init(cub);
		player_settings(cub);
		return (cub);
	}
	else if (act == ACT_GET && cub)
		return (cub);
	else if (act == ACT_FREE && cub)
		return (xfree((void **)&cub), NULL);
	return (NULL);
}

void	g_exit(void)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		cub->stop_handler = 1;
		while (cub->stop_handler < 5)
			continue ;
		_g_exit();
	}
}
