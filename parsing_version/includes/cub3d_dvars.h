/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_dvars.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:43:44 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 09:56:25 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DVARS_H
# define CUB3D_DVARS_H

typedef struct dvar_s
{
	int		id;
	int		ivalue;
	double	dvalue;
	t_vec2f	flimit;
	t_vec2	ilimit;
	int		default_ivalue;
	double	default_dvalue;
}	t_dvars;

int		getvarint(int id);
void	init_dvars(t_cb *cub);
void	setdvar(int id, double v);
void	setdvarint(int id, int v);
double	getvar(int id);
t_dvars	reg_var(int id, double dval, t_vec2f m);
t_dvars	*get_dvar(int id);
#endif