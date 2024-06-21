/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_img_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:13:15 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/17 17:10:03 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

static void	update_splitted_name(char *buffer, size_t len, int i)
{
	buffer[len] = 0x30 + (i / 100);
	buffer[len + 1] = 0x30 + ((i / 10) % 10);
	buffer[len + 2] = 0x30 + (i % 10);
	buffer[len + 3] = 0;
}

static void	split(t_shaders **imgx, t_vec3 wh, int i)
{
	t_vec4	ifr;
	t_vec2	adr;

	ifr.x = i * wh.x;
	ifr.y = 0;
	while (ifr.y < wh.y)
	{
		ifr.z = 0;
		ifr.w = ifr.x + ifr.z;
		while (ifr.w < ifr.x + wh.x)
		{
			adr.x = ifr.y * imgx[0]->img.len + ifr.w * (imgx[0]->img.bpp / 8);
			adr.y = ifr.y * imgx[1]->img.len + ifr.z * (imgx[1]->img.bpp / 8);
			set_value(imgx[1]->img.addr + adr.y, 0);
			if (get_value(imgx[0]->img.addr + adr.x) != 0xFF000000)
				set_value(imgx[1]->img.addr + adr.y,
					get_value(imgx[0]->img.addr + adr.x));
			ifr.z++;
			ifr.w = ifr.x + ifr.z;
		}
		ifr.y++;
	}
}

int	split_image(char *name, char *output, int width, int i)
{
	t_shaders	*imgx[2];
	char		*buffer;
	int			u;

	u = 0;
	if (xalloc((void **)&buffer, sizeof(char), xstrlen(output) + 5))
	{
		imgx[0] = get_img(name);
		xmemcpy(buffer, output, xstrlen(output));
		if (imgx[0])
		{
			while (u < (imgx[0]->img.width / width))
			{
				update_splitted_name(buffer, xstrlen(output), i + u);
				create_img((t_ui){0, 0, width, imgx[0]->img.height, 0},
					NULL, buffer);
				imgx[1] = get_img(buffer);
				if (imgx[1])
					split(imgx, (t_vec3){width, imgx[0]->img.height, 0}, u);
				u++;
			}
		}
		xfree((void **)&buffer);
	}
	return (i + u);
}
