/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_player.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:37:53 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/15 12:00:50 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PLAYER_H
# define CUB3D_PLAYER_H

typedef struct player_s
{
	int			health;
	int			score;
	int			flashlight;
	t_vec2f		origin;
	t_vec2f		dir;
	t_vec2f		plane;
	float		vangle;
	double		speed;
	float		velocity;
	t_weapon	*weapon;
}	t_player;

void	player_settings(t_cb *cub);
void	p_reg_commands(void);
void	pmove_forward(void);
void	pmove_backward(void);
void	plook_right(void);
void	plook_left(void);
void	plook_up(void);
void	plook_down(void);
void	pswitchweapon(void);
int		check_move(t_cb *cub, t_vec2 v);
#endif