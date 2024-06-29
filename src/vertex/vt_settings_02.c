/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vt_settings_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:38:54 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/29 00:53:07 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

void	ml_overwrite_fix(t_prim *s, t_vec4 *ijt)
{
	if (ijt->w >= s->savemesh->height)
		ijt->w = s->savemesh->height - 1;
	else if (ijt->w < 0)
		ijt->w = 0;
	if (ijt->y >= s->savemesh->width)
		ijt->y = s->savemesh->width - 1;
	else if (ijt->y < 0)
		ijt->y = 0;
}

void	ml_overwrite(t_prim *s, int overwrite)
{
	if (overwrite >= 0 && overwrite < 2)
		s->overwrite = overwrite;
}

void	create_img_mesh(t_prim *s, char *name)
{
	int			i;
	t_vec2		min;
	t_vec2		max;
	t_vec2		wh;
	t_shaders	*sh;

	i = 0;
	if (s->cpoint > 0)
	{
		min = s->point[0];
		max = s->point[0];
		while (i < s->cpoint)
		{
			if (s->point[i].x < min.x)
				min.x = s->point[i].x;
			else if (s->point[i].x > max.x)
				max.x = s->point[i].x;
			if (s->point[i].y < min.y)
				min.y = s->point[i].y;
			else if (s->point[i].y > max.y)
				max.y = s->point[i].y;
			i++;
		}
		if (max.x < 0)
			max.x *= -1;
		if (min.x < 0)
			min.x *= -1;
		wh.x = max.x - min.x;
		if (max.y < 0)
			max.y *= -1;
		if (min.y < 0)
			min.y *= -1;
		wh.y = max.y - min.y;
		if (wh.x > 1 && wh.y > 1)
		{
			if (get_img(name) == NULL)
				create_img((t_ui){0, 0, wh.x, wh.y, 0}, fill_img_color, name);
			sh = get_img(name);
			if (sh)
			{
				ml_savemesh(s, sh);
				ml_overwrite(s, s->overwrite);
				ml_end(s);
			}
		}
	}
}


void	export_img(char *name)
{
	int			fd;
	t_shaders	*sh;
	t_shaders	tmp;
	char		buffer[200];

	sh = get_img(name);
	if (sh)
	{
		xmemset(buffer, 0, 200);
		xstrcpy(buffer, "./export/");
		xstrcpy(buffer + xstrlen(buffer), name);
		xstrcpy(buffer + xstrlen(buffer), ".bin\0");
		fd = open(buffer, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd > 0)
		{
			xmemcpy(&tmp, sh, sizeof(t_shaders));
			tmp.next = NULL;
			tmp.created = 0;
			tmp.is_stored = 0;
			tmp.img.ptr = NULL;
			tmp.img.addr = NULL;
			xwrite(fd, &tmp, sizeof(t_shaders));
			xwrite(fd, sh->img.addr, sh->img.height * sh->img.len + sh->img.width * (sh->img.bpp / 8));
			close(fd);
		}
	}
}

void	load_exported(char *name)
{
	t_shaders	tmp;
	t_shaders	*sh;
	int			fd;
	char		*nm;
	ssize_t		p;

	nm = xstrrchr(name, '/');
	if (!get_img(nm))
	{
		fd = open(name, O_RDONLY, 777);
		if (fd > 0)
		{
			p = read(fd, &tmp, sizeof(tmp));
			create_img((t_ui){0, 0, tmp.img.width, tmp.img.height, 0}, fill_img_color, nm);
			sh = get_img(nm);
			if (sh)
			{
				p = read(fd, sh->img.addr, sh->img.height * sh->img.len + sh->img.width * (sh->img.bpp / 8));
				(void)p;
			}
			close(fd);
		}
	}
}
