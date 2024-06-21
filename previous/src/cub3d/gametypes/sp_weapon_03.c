/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_weapon_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:45:03 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/19 12:27:36 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	asset_data_stock(t_vec2 u, t_weapon *cur, t_weapon_data *data)
{
	xstrcpy(cur->info_buffer + xstrlen(cur->info_buffer), " / ");
	u.x = (data->max_ammo_stock < 100) + (data->max_ammo_stock < 10);
	u.y = xstrlen(cur->info_buffer);
	while (u.x < 3)
	{
		if (data->max_ammo_stock >= 100 && u.x == 0)
			cur->info_buffer[u.y] = 0x30 + (cur->ammo_stock / 100);
		else if (data->max_ammo_stock >= 10 && u.x == 1)
			cur->info_buffer[u.y] = 0x30 + ((cur->ammo_stock / 10) % 10);
		else if (u.x == 2)
			cur->info_buffer[u.y] = 0x30 + (cur->ammo_stock % 10);
		u.x++;
		u.y++;
	}
}

void	asset_data_clip(t_weapon *cur, t_weapon_data *data)
{
	t_vec2	u;

	xstrcpy(cur->info_buffer, data->name);
	cur->info_buffer[xstrlen(cur->info_buffer)] = '\n';
	u.x = (data->max_ammo_clip < 100) + (data->max_ammo_clip < 10);
	u.y = xstrlen(cur->info_buffer);
	while (u.x < 3)
	{
		if (data->max_ammo_clip >= 100 && u.x == 0)
			cur->info_buffer[u.y] = 0x30 + (cur->ammo_clip / 100);
		else if (data->max_ammo_clip >= 10 && u.x == 1)
			cur->info_buffer[u.y] = 0x30 + ((cur->ammo_clip / 10) % 10);
		else if (u.x == 2)
			cur->info_buffer[u.y] = 0x30 + (cur->ammo_clip % 10);
		u.x++;
		u.y++;
	}
	asset_data_stock(u, cur, data);
}

void	cbuffer_img(t_shaders *dest, t_shaders *base, t_vec2 at)
{
	__uint32_t	adr;
	t_vec2		i;

	i = (t_vec2){0, 0};
	if (dest && base)
	{
		while (i.y < base->img.height)
		{
			i.x = 0;
			while (i.x < base->img.width)
			{
				if ((at.x + i.x) >= 0 && (at.x + i.x) < dest->img.width
					&& (at.y + i.y) >= 0 && (at.y + i.y) < dest->img.height)
				{
					adr = get_px_color(&base->img, i);
					if (is_valid_color(adr))
						set_color(&dest->img, get_px_adr(&dest->img,
								(t_vec2){at.x + i.x, at.y + i.y}), adr);
				}
				i.x++;
			}
			i.y++;
		}
	}
}

int	cspacing(char c)
{
	if (c >= '0' && c <= '9')
		return (17);
	else if (c >= 'a' && c <= 'z')
	{
		if (c == 'w')
			return (21);
		else
			return (16);
	}
	else if (c == ' ')
		return (8);
	if (c == 'W')
		return (24);
	return (19);
}

void	ctypewritter(char *str, t_vec2 v)
{
	size_t	i;
	char	m[17];
	int		c;

	i = 0;
	c = v.x;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			v.y += 26;
			v.x = c;
			i++;
			continue ;
		}
		xmemcpy(m, "\0", 17);
		if (str[i] >= '!' && str[i] <= '~')
		{
			xmemcpy(m, "monospace_000\0", 17);
		}
		m[11] = 0x30 + (((str[i] - 0x21) / 10) % 10);
		m[12] = 0x30 + ((str[i] - 0x21) % 10);
		cbuffer_img(get_img("framework"), get_img(m),
			(t_vec2){v.x, v.y});
		v.x += cspacing(str[i]);
		i++;
	}
}

void	display_weapon_info(void)
{
	t_cb			*cub;
	t_weapon		*cur;
	t_weapon_data	*data;
	t_ml			*lx;
	t_prim			p;

	lx = gmlx(ACT_GET);
	cub = g_cub(ACT_GET);
	if (lx && cub)
	{
		cur = cub->player.weapon;
		data = &cub->weapons[cur->id];
		xmemset(cur->info_buffer, 0, 64);
		asset_data_clip(cur, data);
		p = ml_begin(ML_PRIM_QUADS);
		ml_vertex(&p, (t_vec2){lx->width - 140, lx->height - 205});
		ml_vertex(&p, (t_vec2){lx->width - 0, lx->height - 205});
		ml_vertex(&p, (t_vec2){lx->width - 0, lx->height - 140});
		ml_vertex(&p, (t_vec2){lx->width - 140, lx->height - 140});
		ml_color(&p, 0x7F0000);
		ml_savemesh(&p, get_img("framework"));
		ml_end(&p);
		p = ml_begin(ML_PRIM_QUADS);
		ml_vertex(&p, (t_vec2){lx->width - 140, lx->height - 205});
		ml_vertex(&p, (t_vec2){lx->width - 0, lx->height - 205});
		ml_vertex(&p, (t_vec2){lx->width - 0, lx->height - 140});
		ml_vertex(&p, (t_vec2){lx->width - 140, lx->height - 140});
		ml_color(&p, 0x7F0000);
		ml_savemesh(&p, get_img("framework"));
		ml_end(&p);
		p = ml_begin(ML_PRIM_QUADS);
		ml_vertex(&p, (t_vec2){5, lx->height - 205});
		ml_vertex(&p, (t_vec2){139, lx->height - 205});
		ml_vertex(&p, (t_vec2){139, lx->height - 198});
		ml_vertex(&p, (t_vec2){5, lx->height - 198});
		ml_color(&p, 0x030303);
		ml_savemesh(&p, get_img("framework"));
		ml_end(&p);
		p = ml_begin(ML_PRIM_QUADS);
		ml_vertex(&p, (t_vec2){7, lx->height - 203});
		ml_vertex(&p, (t_vec2){7 + cub->player.health, lx->height - 203});
		ml_vertex(&p, (t_vec2){7 + cub->player.health, lx->height - 200});
		ml_vertex(&p, (t_vec2){7, lx->height - 200});
		ml_color(&p, 0xFFFFFF);
		ml_savemesh(&p, get_img("framework"));
		ml_end(&p);
		p = ml_begin(ML_PRIM_QUADS);
		ml_vertex(&p, (t_vec2){5, lx->height - 196});
		ml_vertex(&p, (t_vec2){139, lx->height - 196});
		ml_vertex(&p, (t_vec2){139, lx->height - 160});
		ml_vertex(&p, (t_vec2){5, lx->height - 160});
		ml_color(&p, 0x030303);
		ml_savemesh(&p, get_img("framework"));
		ml_end(&p);
		ctypewritter(cur->info_buffer, (t_vec2){lx->width - 120, lx->height - 200});
		ctypewritter("$500999", (t_vec2){0, lx->height - 194});
	}
}
