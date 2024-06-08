/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_img_register.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 06:21:01 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/08 20:12:59 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

static void	store_shaders(t_shaders *new)
{
	t_ml		*lx;
	t_shaders	*sh;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		sh = &lx->texture.shaders;
		if (!sh->is_stored)
		{
			xmemcpy(sh, new, sizeof(t_shaders));
			sh->is_stored = 1;
			sh->next = NULL;
		}
		else
		{
			while (sh && sh->next)
				sh = sh->next;
			if (xalloc((void **)&sh->next, sizeof(t_shaders), 1))
			{
				xmemcpy(sh->next, new, sizeof(t_shaders));
				sh->next->is_stored = 1;
			}
		}
		lx->texture.shaders_count += 1;
	}
}

void	create_img(t_ui ui, void (*func)(), char *name)
{
	t_ml		*lx;
	t_shaders	box;

	lx = gmlx(ACT_GET);
	if (lx && get_img(name) == NULL)
	{
		xmemset(&box, 0, sizeof(t_shaders));
		box.file = xhashstr(name);
		box.img.height = ui.h;
		box.img.width = ui.w;
		box.created = 1;
		box.next = NULL;
		box.img.ptr = mlx_new_image(lx->ptr, ui.w, ui.h);
		if (!box.img.ptr)
			return ;
		box.img.addr = mlx_get_data_addr(box.img.ptr,
				&box.img.bpp, &box.img.len, &box.img.endian);
		if (!box.img.addr)
			return ;
		if (func == fill_img_color)
			func(&box.img, ui.color);
		else if (func)
			func(&box.img, ui);
		store_shaders(&box);
	}
}

void	register_img(char *path)
{
	t_ml		*lx;
	t_shaders	sh;
	int			fd;

	lx = gmlx(ACT_GET);
	fd = open(path, O_RDONLY);
	if (fd > 0 && lx && !get_img(xstrrchr(path, '/')))
	{
		close(fd);
		sh.created = 0;
		sh.img.ptr = mlx_xpm_file_to_image(lx->ptr,
				path, &sh.img.width, &sh.img.height);
		sh.img.addr = mlx_get_data_addr(sh.img.ptr,
				&sh.img.bpp, &sh.img.len, &sh.img.endian);
		sh.file = xhashstr(xstrrchr(path, '/'));
		sh.next = NULL;
		store_shaders(&sh);
	}
}
