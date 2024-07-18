/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_img_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:03:40 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 12:16:59 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief insert pixel and fix if x is out of window
/// @param d image to print
/// @param xs position to print
/// @param xy current pixel 
/// @param rs get pixel of the image
static void	blitting_inc(t_shaders *d, t_vec2 xs, t_vec2 *xy, t_vec2 *rs)
{
	__uint32_t	c;

	c = get_px_color(&d->img, *rs);
	if (is_valid_color(c))
		ml_put_pixel(xs.x + xy->x, xs.y + xy->y, c);
	rs->x++;
	if (rs->x >= d->img.width)
		rs->x = 0;
	xy->x++;
}

/// @brief print a image into the window via ml_put_pixel,
/// if the dimension is bigger than the image the image 
///will be repeated
/// @param xs position to print
/// @param dim dimension
/// @param name name of the shader
void	blitting_render(t_vec2 xs, t_vec2 dim, char *name)
{
	t_vec2		rs;
	t_vec2		xy;
	t_shaders	*d;

	rs = (t_vec2){0, 0};
	xy = (t_vec2){0, 0};
	d = get_img(name);
	if (d)
	{
		while (xy.y < dim.y)
		{
			rs.x = 0;
			xy.x = 0;
			while (xy.x < dim.x)
				blitting_inc(d, xs, &xy, &rs);
			rs.y++;
			if (rs.y >= d->img.height)
				rs.y = 0;
			xy.y++;
		}
	}
}

/// @brief check if the current color is correct
/// @param c color
/// @return 
int	is_valid_color(__uint32_t c)
{
	return ((c != 0 && c != 0xFF000000));
}
