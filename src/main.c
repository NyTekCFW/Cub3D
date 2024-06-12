/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:05:05 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/12 09:32:29 by lchiva           ###   ########.fr       */
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
void	buffer_img(t_shaders *dest, t_shaders *base, t_vec2 at)
{
	__uint32_t	adr;
	t_vec2		i;

	i = (t_vec2){0, 0};
	if (dest && base)
	{
		while (i.y < base->img.height)
		{
			i.x = 0;
			while (i.x < base->img.width)
			{
				if ((at.x + i.x) >= 0 && (at.x + i.x) < dest->img.width
					&& (at.y + i.y) >= 0 && (at.y + i.y) < dest->img.height)
				{
					adr = get_px_color(&base->img, get_px_adr(&base->img, i));
					if (is_valid_color(adr))
						set_color(&dest->img, get_px_adr(&dest->img,
								(t_vec2){at.x + i.x, at.y + i.y}), adr);
				}
				i.x++;
			}
			i.y++;
		}
	}
}

void	build_weapon(t_ml *lx)
{
	t_cb		*cub;
	t_weapon	*wpn;
	t_vec2		u;
	t_vec2		i;
	char		m[15];

	cub = g_cub(ACT_GET);
	i.x = 0;
	i.y = 0;
	if (cub)
	{
		wpn = &cub->player.weapon;
		u.x = lx->width - 288;
		u.y = lx->height - 64;
		i.x = 0;
		if (wpn->max_ammo_clip < 100)
			i.x++;
		if (wpn->max_ammo_clip < 10)
			i.x++;
		while (i.x < 3)
		{
			xmemcpy(m, "counter_000\0", 15);
			if (i.x == 0)
				m[10] = 0x30 + (wpn->ammo_clip / 100);
			else if (i.x == 1)
				m[10] = 0x30 + ((wpn->ammo_clip / 10) % 10);
			else if (i.x == 2)
				m[10] = 0x30 + (wpn->ammo_clip % 10);
			buffer_img(get_img("framework"), get_img(m), (t_vec2){u.x + (24 * i.x), u.y});
			i.x++;
		}
	}
}

void	typewritter(char *str, t_vec2 v)
{
	size_t	i;
	char	m[15];
	int		c;

	i = 0;
	while (str[i])
	{
		c = 0;
		xmemcpy(m, "\0", 15);
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			xmemcpy(m, "uletter_000\0", 15);
			c = 'A';
		}
		else if (str[i] >= 'a' && str[i] <= 'z')
		{
			xmemcpy(m, "lletter_000\0", 15);
			c = 'a';
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			xmemcpy(m, "counter_000\0", 15);
			c = '0';
		}
		m[9] = 0x30 + (((str[i] - c) / 10) % 10);
		m[10] = 0x30 + ((str[i] - c) % 10);
		buffer_img(get_img("framework"), get_img(m),
			(t_vec2){v.x + (i * 24), v.y});
		i++;
	}
}
/*
char		m[15];
		while (i < 26)
		{
			xmemcpy(m, "lletter_000\0", 15);
			m[9] = 0x30 + ((i / 10) % 10);
			m[10] = 0x30 + (i % 10);
			buffer_img(get_img("framework"), get_img(m), (t_vec2){i * 28, 300});
			i++;
		}
*/
int	display(t_ml *lx)
{
	if (lx->refresh  || move)
	{
		lx->refresh = 0;
		//lx->purge_window();
		//print_img((t_vec2){0, 0}, "skybox_cub3d");
		//print_img((t_vec2){0, 0}, "icon_minimap");
		//t_players f;
		//	init_player(&f);
		//return ;
		raycasting();
		build_weapon(lx);
		buffer_img(get_img("framework"), get_img("icon_minimap"), (t_vec2){0, 0});
		typewritter("Hold F to open", (t_vec2){0, 300});
		print_img((t_vec2){0, 0}, "framework");
		
		//draw_cone();
		//generate_minimap();
		//drawplayer();
	//	drawrays3d();
		move = 0;
	}
	return (1);
}


void move_forward(t_cb *cub)
{
    t_player *player = &cub->player;
    if (cub->map_data.map[(int)(player->origin.y) / cub->minimap.dimension][(int)(player->origin.x + player->dir.x * 0.1) / cub->minimap.dimension] == '0')
        player->origin.x += player->dir.x * 0.1;
    if (cub->map_data.map[(int)(player->origin.y + player->dir.y * 0.1) / cub->minimap.dimension][(int)(player->origin.x) / cub->minimap.dimension] == '0')
        player->origin.y += player->dir.y * 0.1;
}

void move_backward(t_cb *cub)
{
    t_player *player = &cub->player;
    if (cub->map_data.map[(int)(player->origin.y / cub->minimap.dimension)][(int)(player->origin.x - player->dir.x * 0.1)  / cub->minimap.dimension] == '0')
        player->origin.x -= player->dir.x * 0.1;
    if (cub->map_data.map[(int)(player->origin.y - player->dir.y * 0.1)  / cub->minimap.dimension][(int)(player->origin.x)  / cub->minimap.dimension] == '0')
        player->origin.y -= player->dir.y * 0.1;
}

void move_left(t_cb *cub)
{
    t_player *player = &cub->player;
    double old_dir_x = player->dir.x;
    player->dir.x = player->dir.x * cos(-0.1) - player->dir.y * sin(-0.1);
    player->dir.y = old_dir_x * sin(-0.1) + player->dir.y * cos(-0.1);
    double old_plane_x = player->plane.x;
    player->plane.x = player->plane.x * cos(-0.1) - player->plane.y * sin(-0.1);
    player->plane.y = old_plane_x * sin(-0.1) + player->plane.y * cos(-0.1);
}

void move_right(t_cb *cub) 
{
    t_player *player = &cub->player;
    double old_dir_x = player->dir.x;
    player->dir.x = player->dir.x * cos(0.1) - player->dir.y * sin(0.1);
    player->dir.y = old_dir_x * sin(0.1) + player->dir.y * cos(0.1);
    double old_plane_x = player->plane.x;
    player->plane.x = player->plane.x * cos(0.1) - player->plane.y * sin(0.1);
    player->plane.y = old_plane_x * sin(0.1) + player->plane.y * cos(0.1);
}

int hook_keyboard(int keycode, t_ml *lx)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (keycode == XK_w) // Flèche haut
		move_forward(cub);
    else if (keycode == XK_s) // Flèche bas
		move_backward(cub);
    else if (keycode == XK_a) // Flèche gauche
		move_left(cub);
    else if (keycode == XK_d) // Flèche droite
		move_right(cub);
	else if (keycode == XK_y)
		cub->player.vangle += 0.1;//1.5max
	else if (keycode == XK_u)
		cub->player.vangle -= 0.1;//-0.8max
	else if (keycode == XK_v)
		cub->player.weapon.ammo_clip -= 1;
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
			register_img("./textures/fonts/digits.xpm");
			register_img("./textures/fonts/alpha_upper.xpm");
			register_img("./textures/fonts/alpha_lower.xpm");
			register_img("./textures/link_head.xpm");
			split_image("/digits.xpm", "counter_", 23, 0);
			split_image("/alpha_upper.xpm", "uletter_", 25, 0);
			split_image("/alpha_lower.xpm", "lletter_", 25, 0);
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
//https://smallseotools.com/text-to-image/