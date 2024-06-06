/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:07:00 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/06 03:36:05 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "openmlx.h"

//minimap
typedef struct mm_s
{
	t_vec2	origin;
	float	scale;
	int		dimension;
	int		view_filled;
	int		width;
	int		height;
	int		size;
	int		min;
}	t_mm;

typedef struct player_s
{
	t_vec2	mm_origin;
	t_vec2	origin;
}	t_player;

typedef struct cb_s
{
	t_mm		minimap;
	t_player	player;
}	t_cb;

t_cb	*g_cub(int act);
void	generate_minimap(void);
void	get_porigin(void);
#endif
