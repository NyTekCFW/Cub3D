/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_lx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:14:55 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/28 18:56:43 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief Initialise Get and Free all data
///about the window
/// @param e_gmlxact ACT_INIT | ACT_GET | ACT_FREE
/// @return a ptr of t_ml *lx static struct or NULL
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
