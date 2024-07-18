/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:34:11 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 06:57:15 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	_g_exit(void)
{
	int	i;
	int	n;
	int	*p;

	i = -1;
	p = get_key_count();
	n = *p;
	*p = 0;
	while (++i < n)
		keynum_replace(i, NULL);
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
	t_ml	*lx;
	t_cb	*cub;

	lx = gmlx(ACT_GET);
	cub = g_cub(ACT_GET);
	if (cub && lx)
	{
		cub->stop_handler = 1;
		mlx_loop_end(lx->ptr);
		while (cub->stop_handler < 2)
			continue ;
		_g_exit();
	}
}
