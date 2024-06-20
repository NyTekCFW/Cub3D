/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_weapon_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:54:08 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/20 08:39:46 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	get_weapon_by_name(char *name)
{
	t_cb	*cub;
	int		i;

	i = 0;
	cub = g_cub(ACT_GET);
	if (cub)
	{
		while (i < WPN_MAX)
		{
			if (cub->weapons[i].debugname == fnv1a_hash(name))
				return (cub->weapons[i].id);
			i++;
		}
	}
	return (0);
}

void	give_weapon(char *name)
{
	t_weapon	*weap;
	t_cb		*cub;
	int			id;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		weap = cub->player.weapon;
		if (weap)
		{
			id = get_weapon_by_name(name);
			weap->id = id;
			weap->ammo_clip = cub->weapons[id].max_ammo_clip;
			weap->ammo_stock = cub->weapons[id].start_ammo_stock;
			weap->reloading = 0;
			weap->no_ammo = 0;
		}
	}
}

void	give_max_ammo(void)
{
	t_weapon	*weap;
	t_cb		*cub;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		weap = cub->player.weapon;
		if (weap)
		{
			weap->ammo_clip = cub->weapons[weap->id].max_ammo_clip;
			weap->ammo_stock = cub->weapons[weap->id].max_ammo_stock;
			weap->reloading = 0;
			weap->no_ammo = 0;
		}
	}
}

void	take_weapon(void)
{
	t_weapon	*weap;
	t_cb		*cub;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		weap = cub->player.weapon;
		if (weap)
		{
			weap->ammo_clip = cub->weapons[WPN_NONE].max_ammo_clip;
			weap->ammo_stock = cub->weapons[WPN_NONE].max_ammo_stock;
			weap->id = WPN_NONE;
			weap->reloading = 0;
			weap->no_ammo = 0;
		}
	}
}
