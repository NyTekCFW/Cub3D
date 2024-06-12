/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:07:02 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/10 03:38:13 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

#define MAP_HEIGHT 4
#define MAP_WIDTH 24

char g_mapc[MAP_HEIGHT][MAP_WIDTH] =
{
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

void	map_init(t_cb *cub)
{
	cub->map_data.map = (char **)malloc(sizeof(char *) * MAP_HEIGHT);
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		cub->map_data.map[i] = (char *)malloc(sizeof(char) * MAP_WIDTH);
		memcpy(cub->map_data.map[i], g_mapc[i], sizeof(char) * MAP_WIDTH);
	}
	cub->map_data.height = MAP_HEIGHT;
	cub->map_data.width = MAP_WIDTH;
	cub->map_data.dimension = 64;
}
