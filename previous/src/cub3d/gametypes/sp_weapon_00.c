/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_weapon_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:10:54 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/16 20:10:22 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	attribute_data(t_weapon_data *data, char *name, t_vec3 ammo)
{
	data->debugname = fnv1a_hash(name);
	xstrcpy(data->name, name);
	data->max_ammo_clip = ammo.x;
	data->max_ammo_stock = ammo.y;
	data->start_ammo_stock = ammo.z;
}

static void	attribute_wpns(t_weapon_data *data, int i)
{
	if (i == WPN_HAMR)
	{
		attribute_data(&data[i], "HAMR", (t_vec3){75, 500, 425});
		data[i].type = WPN_TYPE_LMG;
		data[i].fire_mode = WPN_MODE_AUTO;
		data[i].rpm = 625;
		data[i].damage = 40;
	}
	else if (i == WPN_DSR)
	{
		attribute_data(&data[i], "DSR-50", (t_vec3){4, 48, 44});
		data[i].type = WPN_TYPE_SNIPER;
		data[i].fire_mode = WPN_MODE_SINGLE_SHOT_LOCK;
		data[i].damage = 98;
		data[i].rpm = 50;
	}
}

static void	attribute_wpn(t_weapon_data *data, int i)
{
	data[i].id = i;
	xmemset(data[i].name, 0, sizeof(data[i].name));
	if (i == WPN_NONE)
	{
		attribute_data(&data[i], "None", (t_vec3){0, 0, 0});
		data[i].type = WPN_TYPE_ERROR;
		data[i].fire_mode = WPN_MODE_AUTO;
		data[i].damage = 0;
		data[i].rpm = 0;
	}
	else if (i == WPN_M1911)
	{
		attribute_data(&data[i], "M1911", (t_vec3){8, 80, 72});
		data[i].type = WPN_TYPE_PISTOL;
		data[i].fire_mode = WPN_MODE_SINGLE_SHOT;
		data[i].damage = 15;
		data[i].rpm = 625;
	}
	attribute_wpns(data, i);
}

void	initial_weapons_data(void)
{
	t_cb			*cub;
	int				i;

	i = 0;
	cub = g_cub(ACT_GET);
	if (cub)
	{
		while (i < WPN_MAX)
		{
			attribute_wpn(cub->weapons, i);
			i++;
		}
	}
}
