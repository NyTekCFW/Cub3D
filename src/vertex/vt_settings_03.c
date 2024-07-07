/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vt_settings_03.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 04:09:00 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/07 19:08:22 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief write the header and data
/// @param buffer exported file
/// @param sh image to export
static void	_export_data(char *buffer, t_shaders *sh)
{
	int			fd;
	t_shaders	tmp;

	fd = open(buffer, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd > 0)
	{
		xmemcpy(&tmp, sh, sizeof(t_shaders));
		tmp.next = NULL;
		tmp.created = 0;
		tmp.is_stored = 0;
		tmp.img.ptr = NULL;
		tmp.img.addr = NULL;
		xwrite(fd, &tmp, sizeof(t_shaders));
		xwrite(fd, sh->img.addr, sh->img.size);
		close(fd);
	}
}

/// @brief export a shader as
///a .bin file
/// @param name name of the 
///image to export
void	export_img(char *name)
{
	t_shaders	*sh;
	char		buffer[128];

	sh = get_img(name);
	if (sh && xstrlen(name) < 100)
	{
		xmemset(buffer, 0, 128);
		xstrcpy(buffer, "./export/");
		xstrcpy(buffer + xstrlen(buffer), name);
		xstrcpy(buffer + xstrlen(buffer), ".bin\0");
		_export_data(buffer, sh);
	}
}

/// @brief register an exported image
/// @param name path + name of the
///exported image e.g :
///./texture/exported/test.bin
///will become /test.bin
///when the register will end
void	register_exp_img(char *name)
{
	t_shaders	tmp;
	t_shaders	*sh;
	ssize_t		p;
	char		*nm;
	int			fd;

	nm = xstrrchr(name, '/');
	if (!get_img(nm))
	{
		fd = open(name, O_RDONLY, 0644);
		if (fd > 0)
		{
			p = read(fd, &tmp, sizeof(tmp));
			create_img((t_ui){tmp.img.width,
				tmp.img.height, 0}, fill_img_color, nm);
			sh = get_img(nm);
			if (sh)
			{
				p = read(fd, sh->img.addr, sh->img.size);
				(void)p;
			}
			close(fd);
		}
	}
}
