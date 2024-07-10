/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_keyboard.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:58:47 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/08 21:10:17 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_KEYBOARD_H
# define OPENMLX_KEYBOARD_H

typedef struct keyboard_hook_s
{
	unsigned short	code;
	unsigned char	is_pressed;
	void			(*(callback))();
}	t_key;

//keycode use key code e.g : XK_W ...
//keynum use the num obtained via
//get_key_num
//keycode functions are more slow
//than keynum functions
//keycode part 
int		get_key_num(__uint16_t code);
int		keycode_is_pressed(__uint16_t code);
int		keycode_execute(__uint16_t code);
void	keycode_replace(__uint16_t code, void (*(func))());
void	set_keycode_status(__uint16_t code, __uint8_t active);
void	add_keycode(__uint16_t code, void (*(func))());
//keynum part
int		keynum_execute(int num);
int		keynum_is_pressed(int num);
int		keynum_execute(int num);
void	keynum_replace(int num, void (*(func))());
void	set_keynum_status(int num, __uint8_t active);
//hook
int		hook_keyboard_r(int ks, void *data);
int		hook_keyboard_p(int ks, void *data);
#endif