/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:05:05 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/09 19:59:03 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <time.h>
# include <pthread.h>

int move = 0;

double px, py,pdx,pdy,pa;
int mapx=10, mapy=9, maps=32;
int cell_size = 24;
int lookat = 160;
int map[] =
{
	1,1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,
};

double degToRad(int a) { return a*PI/180.0;}
int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}

#define FOV 60
/*
void draw_cone(void)
{
	t_cb *cub;
	t_map *data;
	t_player *p;
	t_prim g;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		data = &cub->map_data;
		p = &cub->player;
		g = ml_begin(ML_PRIM_POLYGON);
		ml_vertex(&g, (t_vec2){(int)p->origin.x, (int)p->origin.y});
		cone_begin(data, p, &cub->minimap, &g);
		ml_color(&g, 0xFFFF00);
		ml_setmode(&g, 1);
		ml_size(&g, 1);
		ml_end(&g);
	}
}*/

int	display(t_ml *lx)
{
	if (lx->refresh  || move)
	{
		lx->refresh = 0;
		lx->purge_window();
		print_img((t_vec2){0, 0}, "skybox_cub3d");
		print_img((t_vec2){0, 0}, "icon_minimap");
		//t_players f;
		//	init_player(&f);
		//return ;
		raycasting();
		print_img((t_vec2){0, 0}, "framework");
		//draw_cone();
		//generate_minimap();
		//drawplayer();
	//	drawrays3d();
		move = 0;
	}
	return (1);
}

static int	hook_keyboard(int ks, t_ml *lx)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	(void)ks;
	if (cub)
	{
		if (ks == XK_w)
		{
			cub->player.origin.x += 0.2;//cub->player.pad.x;
			cub->player.origin.y += 0.2;//cub->player.pad.y;
			px+=pdx*5; py+=pdy*5;
		}
		else if (ks == XK_s)
		{
			cub->player.origin.x -= 0.2;//cub->player.pad.x;
			cub->player.origin.y -= 0.2;//cub->player.pad.y;
			px-=pdx*5; py-=pdy*5;
		}
		else if (ks == XK_a)
		{
			pa+=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
			//cub->player.angle -= 0.1;
			//if (cub->player.angle <= 0)
			//	cub->player.angle += (PI * 2);
		}
		else if (ks == XK_d)
		{
			pa-=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
			//cub->player.angle += 0.1;
			//if (cub->player.angle >= (PI * 2))
			//	cub->player.angle -= (PI * 2);
		}
		//cub->player.pad.x = cos(cub->player.angle) * 0.2;
		//cub->player.pad.y = sin(cub->player.angle) * 0.2;
	//	printf("angle = %f\n", cub->player.angle);
	}
	lx->refresh = 1;
	move = 1;
	return (1);
}

void	register_hands(void)
{
	int	b;
	int	i;
	char		m[15];

	i = 0;
	b = 0;
	register_img("./textures/hands/hand_anim_001.xpm");
	register_img("./textures/hands/hand_anim_002.xpm");
	register_img("./textures/hands/hand_anim_003.xpm");
	register_img("./textures/hands/hand_anim_004.xpm");
	register_img("./textures/hands/hand_anim_005.xpm");
	register_img("./textures/hands/hand_anim_006.xpm");

	i = split_image("/hand_anim_001.xpm", "hand_anim_", 569, 0);
	i = split_image("/hand_anim_002.xpm", "hand_anim_", 569, i);
	i = split_image("/hand_anim_003.xpm", "hand_anim_", 569, i);
	i = split_image("/hand_anim_004.xpm", "hand_anim_", 569, i);
	i = split_image("/hand_anim_005.xpm", "hand_anim_", 569, i);
	i = split_image("/hand_anim_006.xpm", "hand_anim_", 569, i);
	xmemcpy(m, "hand_anim_000\0", 15);
	while (b <= i)
	{
		m[10] = 0x30 + (b / 100);
		m[11] = 0x30 + ((b / 10) % 10);
		m[12] = 0x30 + (b % 10);
		printf("-> %s\n", m);
		print_img((t_vec2){320, 400}, m);
		usleep(8000);
		b++;
	}
	while (b >= 0)
	{
		m[10] = 0x30 + (b / 100);
		m[11] = 0x30 + ((b / 10) % 10);
		m[12] = 0x30 + (b % 10);
		print_img((t_vec2){320, 400}, m);
		usleep(8000);
		b--;
	}
}

//Setup Exemple
int	main(void)
{
	t_ml		*lx;
	t_cb		*cub;

	lx = gmlx(ACT_INIT);
	cub = g_cub(ACT_INIT);
	if (lx && cub)
	{
		lx->purge_color = 0x7f7f7f;
		if (lx->set_win_size(1280, 720) && lx->make_window("OpenMLX Showcase"))
		{
			//player_init();
			register_img("./textures/brick_argb.xpm");
			register_img("./textures/ground.xpm");
			register_img("./textures/rock.xpm");
			register_img("./textures/link_head.xpm");
			px = cub->player.origin.x;
			py = cub->player.origin.y;
			pa=90;
			pdx=cos(degToRad(pa));
			pdy=-sin(degToRad(pa));
			lx->refresh = 0;
			build_images();
			build_minimap();
			
			//sleep(4);
		//	register_hands();
			
			mlx_loop_hook(lx->ptr, display, lx);
			mlx_hook(lx->win, KeyPress, (1L << 0), hook_keyboard, lx);
			mlx_loop(lx->ptr);
			while (1)
				;
			lx->quit_window();
		}
	}
}
