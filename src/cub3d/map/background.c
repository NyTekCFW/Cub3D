/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:10:03 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/08 20:22:08 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	skybox_build(t_img *dest, t_ui ui)
{
	__uint32_t	size;
	__uint32_t	i;

	i = 0;
	(void)ui;
	if (!dest)
		return ;
	size = dest->height * dest->len
		+ dest->width * (dest->bpp / 8);
	while (i < size)
	{
		if (i < ((size / 2) - (dest->width * 2)))
			set_color(dest, i, 0x7F7F7F);
		else
			set_color(dest, i, 0x3F3F3F);
		i += 4;
	}
}

void	build_images(void)
{
	t_ml	*lx;
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	lx = gmlx(ACT_GET);
	if (lx && cub)
	{
		create_img((t_ui){0, 0, lx->width, lx->height, 0},
			skybox_build, "skybox_cub3d");
		create_img((t_ui){0, 0, cub->minimap.width + 1,
			cub->minimap.height + 1, 0}, fill_img_color, "icon_minimap");
	}
}
