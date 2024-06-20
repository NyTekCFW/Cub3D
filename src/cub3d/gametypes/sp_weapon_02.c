/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_weapon_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:16:42 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/20 08:40:15 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	get_ammo_count(t_weapon *weap, t_weapon_data *data)
{
	int	p;

	p = weap->ammo_stock - (data->max_ammo_clip - weap->ammo_clip);
	if (p <= 0)
		return (weap->ammo_stock);
	return (weap->ammo_stock - p);
}

void	weapon_fired(void)
{
	t_weapon	*weap;
	t_cb		*cub;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		weap = cub->player.weapon;
		if (weap->ammo_stock == 0 && weap->ammo_clip == 0)
			weap->no_ammo = 1;
		if (weap->id != WPN_NONE && !weap->no_ammo && !weap->reloading)
		{
			if (weap->ammo_clip > 0)
			{
				weap->ammo_clip -= 1;
				if (weap->ammo_clip == 0)
					weapon_reload();
			}
		}
	}
}

void	weapon_reload(void)
{
	t_weapon	*weap;
	t_cb		*cub;
	int			p;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		weap = cub->player.weapon;
		if (weap->id != WPN_NONE && !weap->no_ammo && !weap->reloading)
		{
			if (weap->ammo_clip < cub->weapons[weap->id].max_ammo_clip)
			{
				weap->reloading = 1;
				p = get_ammo_count(weap, &cub->weapons[weap->id]);
				weap->ammo_clip += p;
				weap->ammo_stock -= p;
				weap->reloading = 0;
			}
		}
	}
}
