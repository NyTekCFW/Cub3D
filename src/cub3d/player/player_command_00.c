/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_command_00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:12:18 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/14 01:14:21 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	can_walk(t_cb *cub, t_vec2 u)
{
	char	c;

	if (cub && cub->map_data.map)
	{
		c = cub->map_data.map[u.y][u.x];
		if (c == '0' || c == ' ' || c == '\t')
		{
			cub->player.velocity += 0.2;
			if (cub->player.velocity > 1.6f)
				cub->player.velocity = 1.6f;
			return (1);
		}
	}
	return (0);
}

void	pmove_forward(void)
{
	t_cb		*cub;
	t_player	*p;
	t_vec2		v;

	cub = g_cub(ACT_GET);
	p = get_user();
	if (cub && p)
	{
		p->speed = getvar(VAR_G_SPEED);
		v = (t_vec2){(int)(p->origin.x + (p->dir.x * p->speed)),
			(int)(p->origin.y)};
		if (check_move(cub, v) && can_walk(cub, v))
			p->origin.x += p->dir.x * p->speed;
		v = (t_vec2){(int)(p->origin.x),
			(int)(p->origin.y + (p->dir.y * p->speed))};
		if (check_move(cub, v) && can_walk(cub, v))
			p->origin.y += p->dir.y * p->speed;
	}
}

void	pmove_backward(void)
{
	t_cb		*cub;
	t_player	*p;
	t_vec2		v;

	cub = g_cub(ACT_GET);
	p = get_user();
	if (cub && p)
	{
		p->speed = getvar(VAR_G_SPEED);
		v = (t_vec2){(int)(p->origin.x - (p->dir.x * p->speed)),
			(int)(p->origin.y)};
		if (check_move(cub, v) && can_walk(cub, v))
			p->origin.x -= p->dir.x * p->speed;
		v = (t_vec2){(int)(p->origin.x),
			(int)(p->origin.y - p->dir.y * p->speed)};
		if (check_move(cub, v) && can_walk(cub, v))
			p->origin.y -= p->dir.y * p->speed;
	}
}

void	plook_right(void)
{
	t_player	*p;
	double		odir;
	double		oplane;

	p = get_user();
	if (p)
	{
		odir = p->dir.x;
		p->dir.x = p->dir.x * cosf(-0.1) - p->dir.y * sinf(-0.1);
		p->dir.y = odir * sinf(-0.1) + p->dir.y * cosf(-0.1);
		oplane = p->plane.x;
		p->plane.x = p->plane.x * cosf(-0.1) - p->plane.y * sinf(-0.1);
		p->plane.y = oplane * sinf(-0.1) + p->plane.y * cosf(-0.1);
	}
}

void	plook_left(void)
{
	t_player	*p;
	double		odir;
	double		oplane;

	p = get_user();
	if (p)
	{
		odir = p->dir.x;
		p->dir.x = p->dir.x * cosf(0.1) - p->dir.y * sinf(0.1);
		p->dir.y = odir * sinf(0.1) + p->dir.y * cosf(0.1);
		oplane = p->plane.x;
		p->plane.x = p->plane.x * cosf(0.1) - p->plane.y * sinf(0.1);
		p->plane.y = oplane * sinf(0.1) + p->plane.y * cosf(0.1);
	}
}
