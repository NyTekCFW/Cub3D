/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_enum.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 08:02:00 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 08:52:21 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ENUM_H
# define CUB3D_ENUM_H

typedef struct cb_s	t_cb;

//texture
enum e_cub_texture
{
	TEX_WALL_SOUTH	= 0,
	TEX_WALL_NORTH,
	TEX_WALL_EAST,
	TEX_WALL_WEST,
	TEX_GROUND,
	TEX_CEILING,
	TEX_RENDER
};

//dvars
enum e_dvars_type
{
	VAR_ERROR		= -1,
	VAR_G_GRAVITY,
	VAR_G_SPEED,
	VAR_SHADOWS,
	VAR_FLASHLIGHT_RADIUS,
	VAR_GUN_X,
	VAR_GUN_Y,
	VAR_FPS,
	VAR_TIMESCALE,
	VAR_ASPECT,
	VAR_MAX
};

//weapons
enum e_weapons
{
	WPN_NONE	= 0,
	WPN_M1911,
	WPN_MAX
};

enum e_weapons_type
{
	WPN_TYPE_ERROR = -1,
	WPN_TYPE_PISTOL
};

enum e_weapons_frame
{
	WPN_FRAME_WALK	= 0,
	WPN_FRAME_AIM,
	WPN_FRAME_FIRE,
	WPN_FRAME_AIMFIRE,
	WPN_FRAME_RELOAD
};

enum e_weapons_fire_mode
{
	WPN_MODE_AUTO = 0,
	WPN_MODE_SINGLE_SHOT
};

#endif