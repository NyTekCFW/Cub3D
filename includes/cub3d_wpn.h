/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_wpn.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:24:54 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/13 08:03:40 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_WPN_H
# define CUB3D_WPN_H

typedef struct weapon_data_s
{
	char		name[32];
	int			frame[5];
	int			id;
	int			type;
	__uint32_t	debugname;
	__uint32_t	max_ammo_stock;
	__uint32_t	max_ammo_clip;
	__uint32_t	start_ammo_stock;
	__uint32_t	damage;
	__uint32_t	fire_mode;
	__uint32_t	rpm;
}	t_weapon_data;

typedef struct weapon_s
{
	int			id;
	int			no_ammo;
	int			reloading;
	__uint32_t	ammo_stock;
	__uint32_t	ammo_clip;
	char		info_buffer[64];
	char		anim_buffer[64];
}	t_weapon;

void	weapon_reload(void);
void	weapon_fired(void);
void	take_weapon(void);
void	give_max_ammo(void);
void	give_weapon(char *name);
void	get_weapon_info(void);
void	run_weapon_anim(void);
t_vec2	*get_move_render(void);
#endif