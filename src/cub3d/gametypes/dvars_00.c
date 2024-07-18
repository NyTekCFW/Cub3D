/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvars_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:47:09 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 10:19:08 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	fix_value(double *v, t_vec2f *m)
{
	double	tmp;

	if ((__int64_t)(*v) > 2147483647)
		*v = (double)2147483647;
	else if ((__int64_t)(*v) < -2147483648)
		*v = (double)-2147483648;
	if ((__int64_t)m->x > 2147483647)
		m->x = (double)2147483647;
	else if ((__int64_t)m->x < -2147483648)
		m->x = (double)-2147483648;
	if ((__int64_t)m->y > 2147483647)
		m->y = (double)2147483647;
	else if ((__int64_t)m->y < -2147483648)
		m->y = (double)-2147483648;
	if (m->x > m->y)
	{
		tmp = m->x;
		m->x = m->y;
		m->y = tmp;
	}
}

t_dvars	reg_var(int id, double dval, t_vec2f m)
{
	t_dvars	var;
	fix_value(&dval, &m);
	var.id = id;
	var.dvalue = dval;
	var.ivalue = (int)dval;
	var.flimit = m;
	var.ilimit = (t_vec2){(int)m.x, (int)m.y};
	var.default_dvalue = var.dvalue;
	var.default_ivalue = var.ivalue;
	return (var);
}

void	setdvar(int id, double v)
{
	t_cb	*cb;
	t_dvars	*var;

	cb = g_cub(ACT_GET);
	if (cb && id > VAR_ERROR && id < VAR_MAX)
	{
		var = &cb->vars[id];
		if (var)
		{
			fix_value(&v, &var->flimit);
			if (v >= var->flimit.x && v <= var->flimit.y)
			{
				var->dvalue = v;
				var->ivalue = (int)v;
			}
		}
	}
}

double	getvar(int id)
{
	t_cb	*cb;
	t_dvars	*var;

	cb = g_cub(ACT_GET);
	if (cb && id > VAR_ERROR && id < VAR_MAX)
	{
		var = &cb->vars[id];
		if (var)
			return (var->dvalue);
	}
	return (1.0);
}

int	getvarint(int id)
{
	t_cb	*cb;
	t_dvars	*var;

	cb = g_cub(ACT_GET);
	if (cb && id > VAR_ERROR && id < VAR_MAX)
	{
		var = &cb->vars[id];
		if (var)
			return (var->ivalue);
	}
	return (1.0);
}
