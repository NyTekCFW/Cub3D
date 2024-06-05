/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_math.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:51:42 by lchiva            #+#    #+#             */
/*   Updated: 2024/05/31 16:14:09 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_MATH_H
# define OPENMLX_MATH_H

typedef struct vec2_s
{
	int	x;
	int	y;
}	t_vec2;

typedef struct vec3_s
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct vec4_s
{
	int	x;
	int	y;
	int	z;
	int	w;
}	t_vec4;

void		set_value(void *adr, __uint32_t val);
__uint32_t	get_value(void *adr);
#endif