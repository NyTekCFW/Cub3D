/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_img_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:34:10 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/19 15:04:08 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

static t_vec3	rgba_to_rgb(__uint32_t clr)
{
	return ((t_vec3){clr & 0xFF, (clr >> 8) & 0xFF, (clr >> 16) & 0xFF});
}

void	set_color(t_img *img, int adr, __uint32_t clr)
{
	t_vec3	rgb;

	rgb = rgba_to_rgb(clr);
	img->addr[adr] = rgb.x;
	img->addr[adr + 1] = rgb.y;
	img->addr[adr + 2] = rgb.z;
}

__uint32_t	get_px_adr(t_img *img, t_vec2 xy)
{
	t_vec2	u;

	u = (t_vec2){xy.x % img->width, xy.y % img->height};
	return (u.y * img->len + u.x * (img->bpp / 8));
}

__uint32_t	get_px_color(t_img *img, t_vec2 xy)
{
	__uint32_t	pick;
	__uint32_t	adr;

	adr = get_px_adr(img, xy);
	pick = img->addr[adr + 2] << 16;
	pick += img->addr[adr + 1] << 8;
	pick += img->addr[adr];
	return (pick);
}

void	fill_img_color(t_img *dest, __uint32_t color)
{
	__uint32_t	size;
	__uint32_t	i;

	i = 0;
	if (!dest)
		return ;
	size = dest->height * dest->len
		+ dest->width * (dest->bpp / 8);
	while (i < size)
	{
		set_color(dest, i, color);
		i += 4;
	}
}
