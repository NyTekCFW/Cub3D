/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_lx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:14:55 by lchiva            #+#    #+#             */
/*   Updated: 2024/05/31 13:57:20 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

t_ml	*gmlx(int e_gmlxact)
{
	static t_ml	*lx;

	if (e_gmlxact == ACT_INIT && xalloc((void **)&lx, 1, sizeof(t_ml)))
	{
		lx->make_window = _ml_create_window;
		lx->set_win_size = _ml_set_window_size;
		lx->purge_window = _ml_purge_window;
		lx->quit_window = _ml_quit;
		lx->new_purge_color = _ml_set_purge_color;
		return (lx);
	}
	else if (e_gmlxact == ACT_GET && lx)
		return (lx);
	else if (e_gmlxact == ACT_FREE && lx)
		return (xfree((void **)&lx), NULL);
	return (NULL);
}
