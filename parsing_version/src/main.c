/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:05:05 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/18 12:19:11 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	register_images(void)
{
	t_ml	*lx;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		create_img((t_ui){lx->width, lx->height, 0}, fill_img_color, "framework");
		register_img("./textures/fonts/monospace_ttf.xpm");
		split_image("/monospace_ttf.xpm", "monospace_", 32, 0);
	}
}

//Setup Exemple
int	main(int ac, char **av)
{
	t_ml		*lx;
	t_cb		*cub;

	lx = gmlx(ACT_INIT);
	if (lx)
	{
		lx->purge_color = 0x7f7f7f;
		if (lx->set_win_size(600, 600) && lx->make_window("OpenMLX Showcase"))
		{
			cub = g_cub(ACT_INIT);
			if (cub)
			{
				if (check_arg(ac, av) && check_file(av[1]))
				{
					if (fill_file_map(cub->map_data.file))
					{
						cub->map_data.texture[0] = find_texture(cub->map_data.file, "NO");
						cub->map_data.texture[1] = find_texture(cub->map_data.file, "SO");
						cub->map_data.texture[2] = find_texture(cub->map_data.file, "WE");
						cub->map_data.texture[3] = find_texture(cub->map_data.file, "EA");
						cub->map_data.texture[4] = find_color(cub->map_data.file, "F");
						cub->map_data.texture[5] = find_color(cub->map_data.file, "C");
						printf("texture : <%s>\n", cub->map_data.texture[0]);
						printf("texture : <%s>\n", cub->map_data.texture[1]);
						printf("Color F : <%s>\n", cub->map_data.texture[4]);
						printf("Color C : <%s>\n", cub->map_data.texture[5]);
						parse_map(cub->map_data.file);
					}
				}
			}
			g_exit(cub);
			lx->quit_window();
		}
	}
	return (1);
}
