/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_command_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 23:56:18 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/15 12:06:33 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	plook_up(void)
{
	t_player	*p;

	p = get_user();
	if (p && p->vangle < 0.8)
	{
		p->vangle += 0.1;
		if (p->vangle >= 0.8)
			p->vangle = 0.8;
	}
}

void	plook_down(void)
{
	t_player	*p;

	p = get_user();
	if (p && p->vangle > -0.8)
	{
		p->vangle -= 0.1;
		if (p->vangle < -0.8)
			p->vangle = -0.8;
	}
}

void	pswitchweapon(void)
{
	t_player	*p;

	p = get_user();
	if (p && p->weapon)
	{
		if (p->weapon->id == WPN_NONE)
			give_weapon("M1911");
		else
			take_weapon();
	}
}
