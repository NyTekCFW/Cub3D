/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_keyboard.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:58:47 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/13 10:47:40 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_KEYBOARD_H
# define OPENMLX_KEYBOARD_H

enum e_button
{
	BUTTON_FIRE	= 0,
	BUTTON_RELOAD,
	BUTTON_FLASHLIGHT,
	BUTTON_JUMP,
	BUTTON_SPRINT,
	BUTTON_STANCE,
	BUTTON_INTERACT,
	BUTTON_LOOK_RIGHT,
	BUTTON_LOOK_LEFT,
	BUTTON_MOVE_FORWARD,
	BUTTON_MOVE_BACKWARD,
	BUTTON_MAX
};

typedef struct keyboard_hook_s
{
	unsigned short	id;
	unsigned short	code;
	unsigned char	is_pressed;
	unsigned char	ignore;
	void			(*(callback))();
}	t_key;

typedef struct config_s
{
	__uint16_t	button[11];
}	t_config;

//keycode use key code e.g : XK_W ...
//keynum use the num obtained via
//get_key_num
//keycode functions are more slow
//than keynum functions
//keycode part 
int		*get_key_count(void);
int		get_key_num(__uint16_t code);
int		keycode_pressed(__uint16_t code);
void	keycode_replace(__uint16_t code, void (*(func))());
void	set_keycode_status(__uint16_t code, __uint8_t active);
void	add_keycode(__uint16_t code, void (*(func))());
//keynum part
t_key	*get_key(__uint8_t id);
int		keynum_execute(int num);
int		key_pressed(int num);
int		keynum_execute(int num);
void	keynum_replace(int num, void (*(func))());
//hook
int		hook_keyboard_r(int ks, void *data);
int		hook_keyboard_p(int ks, void *data);
#endif