/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_dvars.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:43:44 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/24 20:36:28 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DVARS_H
# define CUB3D_DVARS_H

enum e_dvars_type
{
	VAR_ERROR		= -1,
	VAR_TIMESCALE,
	VAR_G_GRAVITY,
	VAR_G_SPEED,
	VAR_SHADOWS,
	VAR_FLASHLIGHT_RADIUS,
	VAR_MAX
};

typedef struct dvar_s
{
	int		id;
	char	type;
	int		ivalue;
	double	dvalue;
	t_vec2f	flimit;
	t_vec2	ilimit;
	int		default_ivalue;
	double	default_dvalue;
}	t_dvars;

t_dvars	reg_var(char t, int id, double dval, t_vec2f m);
void	setdvar(int id, double v);
double	getvar(int id);
void	setdvarint(int id, int v);
int		getvarint(int id);
t_dvars	*get_dvar(int id);
#endif