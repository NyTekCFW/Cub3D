/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_wpn.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:38:06 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/19 14:57:53 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_WPN_H
# define CUB3D_WPN_H

enum e_weapons
{
	WPN_NONE	= 0,
	WPN_M1911,
	WPN_HAMR,
	WPN_DSR,
	WPN_MAX
};

enum e_weapons_type
{
	WPN_TYPE_ERROR = -1,
	WPN_TYPE_PISTOL,
	WPN_TYPE_LMG,
	WPN_TYPE_SNIPER,
};

enum e_weapons_frame
{
	WPN_FRAME_WALK	= 0,
	WPN_FRAME_AIM,
	WPN_FRAME_FIRE,
	WPN_FRAME_AIMFIRE,
	WPN_FRAME_RELOAD,
};

enum e_weapons_fire_mode
{
	WPN_MODE_AUTO = 0,
	WPN_MODE_SINGLE_SHOT,
	WPN_MODE_SINGLE_SHOT_LOCK,
};

typedef struct weapon_data_s
{
	int			id;
	int			type;
	int			frame[5];
	char		name[16];
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
	int			anim_frame;
}	t_weapon;

void	initial_weapons_data(void);
void	display_weapon_info(void);
void	take_weapon(void);
void	give_max_ammo(void);
void	give_weapon(char *name);
void	weapon_fired(void);
void	weapon_reload(void);
void	run_weapon_anim(void);
#endif