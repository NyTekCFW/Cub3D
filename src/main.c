/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:05:05 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/07 23:13:38 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"



void	load_game_textures(t_cb *cub, __uint32_t cg, __uint32_t cc)
{
	t_vec2		u;
	int			i;
	__uint32_t	c[2];
	__uint32_t	adr;

	xmemcpy(c, (__uint32_t []){cg, cc}, sizeof(c));
	u = (t_vec2){0, 0};
	if (cub)
	{
		cub->texture[TEX_WALL_SOUTH] = get_img("/brick_red.xpm");
		cub->texture[TEX_WALL_NORTH] = get_img("/brick_white.xpm");
		cub->texture[TEX_WALL_EAST] = get_img("/cinderblock.xpm");
		cub->texture[TEX_WALL_WEST] = get_img("/roof_brick.xpm");
		cub->texture[TEX_GROUND] = get_img("/dlc2.xpm");
		cub->texture[TEX_CEILING] = get_img("/wall_brownstone.xpm");
		cub->texture[TEX_RENDER] = get_img("framework");
		i = TEX_GROUND;
		while (i < TEX_RENDER)
		{
			if (cub->texture[i])
			{
				if (is_valid_color(c[i - TEX_GROUND]))
				{
					u.y = 0;
					while (u.y < cub->texture[i]->img.height)
					{
						u.x = 0;
						while (u.x < cub->texture[i]->img.height)
						{
							adr = get_px_adr(&cub->texture[i]->img, u);
							if (is_valid_color(*(__uint32_t *)(cub->texture[i]->img.addr + adr)))
								set_color(&cub->texture[i]->img, adr, blend_colors(*(__uint32_t *)(cub->texture[i]->img.addr + adr), c[i - TEX_GROUND], 0.6));
							u.x++;
						}
						u.y++;
					}
				}
			}
			i++;
		}
	}
}

clock_t	timer = 0;

int	display(t_ml *lx)
{
	t_cb		*cub;
	t_screen	*screen;
	char		buffer[32];

	cub = g_cub(ACT_GET);
	if (cub && lx && lx->refresh)
	{
		while (clock() < timer)
			;
		xmemset(buffer, 0, sizeof(buffer));
		xstrcpy(buffer, "FPS : ");
		clock_t dd = clock();
		screen = &cub->screen;
		raycast_env();
		run_weapon_anim();
		merge_img(get_img("framework"), get_img(g_cub(ACT_GET)->player.weapon->anim_buffer), (t_vec2){(screen->x + 300 + (get_move_render()->x * cub->player.velocity)) * getvar(VAR_GUN_X),((screen->y - 35) + (get_move_render()->y * cub->player.velocity)) * getvar(VAR_GUN_Y)});
		
		
		hud_render();
		//draw_safe_area();
		
		if (lx->record.status)
			save_record();
		if (lx->video.status)
			display_video((t_vec2){screen->x, screen->y});
	//	load_video("./export/video.bin\0");
		int tmp = 1000000 / (clock() - dd);
		if (tmp >= 1000)
			buffer[xstrlen(buffer)] = 0x30 + (tmp / 1000);
		if (tmp >= 100)
			buffer[xstrlen(buffer)] = 0x30 + ((tmp / 100) % 10);
		if (tmp >= 10)
			buffer[xstrlen(buffer)] = 0x30 + ((tmp / 10) % 10);
		buffer[xstrlen(buffer)] = 0x30 + (tmp % 10);
		typewritter(buffer, (t_vec2)
		{
			cub->screen.area.a1.x,
			cub->screen.area.a1.y + 300
		});
		print_img((t_vec2){screen->x, screen->y}, "framework");
		timer = clock() + getvarint(VAR_FPS);
		cub->player.velocity -= 0.2;
		if (cub->player.velocity < 0)
			cub->player.velocity = 0;
		//export_img("framework");
	}
	return (1);
}

void	move_forward(t_cb *cub)
{
	t_vec2		v;
	t_player	*player;
	double		speed;

	player = &cub->player;
	speed = getvar(VAR_G_SPEED);
	v = (t_vec2){(int)(player->origin.x + (player->dir.x * speed)), (int)(player->origin.y)};
	if (check_move(cub, v) && cub->map_data.map[v.y][v.x] == '0')
		player->origin.x += player->dir.x * speed;		
	v = (t_vec2){(int)(player->origin.x),
		(int)(player->origin.y + (player->dir.y * speed))};
	if (check_move(cub, v) && cub->map_data.map[v.y][v.x] == '0')
		player->origin.y += player->dir.y * speed;
}

void	move_backward(t_cb *cub)
{
	t_player	*player;
	double		speed;

	player = &cub->player;
	speed = getvar(VAR_G_SPEED);
	if (cub->map_data.map[(int)(player->origin.y)][(int)(player->origin.x - player->dir.x * speed)] == '0')
		player->origin.x -= player->dir.x * speed;
	if (cub->map_data.map[(int)((player->origin.y - player->dir.y * speed))][(int)(player->origin.x)] == '0')
		player->origin.y -= player->dir.y * speed;
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

void	debug_display_player(t_cb *data)
{
	printf("\n---- PLAYER\n");
	printf("Player pos: ");
	printf("x = %f, y = %f\n", data->player.origin.x, data->player.origin.x);
	printf("(x = %f, y = %f)\n", data->player.dir.x, data->player.dir.y);
}

int hook_keyboard(int keycode, t_ml *lx)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
//	debug_display_player(cub);
	if (keycode == XK_w) // Flèche haut
		move_forward(cub);
    else if (keycode == XK_s) // Flèche bas
		move_backward(cub);
    else if (keycode == XK_a) // Flèche gauche
		move_left(cub);
    else if (keycode == XK_d) // Flèche droite
		move_right(cub);
	/*else if (keycode == XK_y)
		cub->player.vangle += 0.1;//1.5max
	else if (keycode == XK_u)
		cub->player.vangle -= 0.1;//-0.8max*/
	else if (keycode == XK_v)
		weapon_fired();
	else if (keycode == XK_b)
		weapon_reload();
	else if (keycode == XK_p)
		start_video("./export/video.bin\0", 0.1);//setdvar(VAR_ASPECT, getvar(VAR_ASPECT) + 0.1);
	else if (keycode == XK_m)
		stop_record();//setdvar(VAR_ASPECT, getvar(VAR_ASPECT) - 0.1);
	else if (keycode == XK_o)
	{
		cub->screen.area.u.y += 1;
		safe_area_update(&cub->screen);
	}
	else if (keycode == XK_l)
	{
		cub->screen.area.u.y -= 1;
		safe_area_update(&cub->screen);
	}
	else if (keycode == XK_Tab)
		take_weapon();
	else if (keycode == XK_q)
		cub->player.flashlight = !cub->player.flashlight;
	lx->refresh = 1;
	cub->player.velocity += 0.2;
	if (cub->player.velocity > 1.6f)
		cub->player.velocity = 1.6f;
	return (1);
}

int	mouse_move(int x, int y, t_cb *cub)
{
	static t_vec2	last;
	t_vec2			delta;
	double			d[4];
	t_ml			*lx;
	t_player		*player;

	lx = gmlx(ACT_GET);
	if (lx && cub)
	{
		player = &cub->player;
		if (player)
		{
			delta = (t_vec2){x - last.x, y - last.y};
			d[0] = 0.0001;
			d[1] = delta.x * d[0];
			d[2] = player->dir.x;
			d[3] = player->plane.x;
			player->dir.x
				= player->dir.x * cos(-d[1]) - player->dir.y * sin(-d[1]);
			player->dir.y = d[2] * sin(-d[1]) + player->dir.y * cos(-d[1]);
			player->plane.x
				= player->plane.x * cos(-d[1]) - player->plane.y * sin(-d[1]);
			player->plane.y = d[3] * sin(-d[1]) + player->plane.y * cos(-d[1]);
			player->vangle -= delta.y * d[0];
			if (player->vangle > 0.8)
				player->vangle = 0.8;
			if (player->vangle < -0.8)
				player->vangle = -0.8;
			last = (t_vec2){lx->width / 2, lx->height / 2};
			lx->refresh = 1;
		}
		if (x != lx->width / 2 || y != lx->height / 2)
			mlx_mouse_move(lx->ptr, lx->win,
				lx->width / 2, lx->height / 2);
	}
	return (0);
}

void	register_xpm(void)
{
	t_ml	*lx;
	t_cb	*cub;
	int		i;

	cub = g_cub(ACT_GET);
	lx = gmlx(ACT_GET);
	if (lx && cub)
	{
		register_exp_img("./export/framework.bin");
		//basic
		register_img("./textures/huds/dpad.xpm");
		register_img("./textures/huds/dpad_bar.xpm");
		register_img("./textures/huds/hud_score.xpm");
		register_img("./textures/huds/crosshair_v.xpm");
		register_img("./textures/huds/crosshair_h.xpm");
		register_img("./textures/brick_argb.xpm");
		register_img("./textures/ground.xpm");
		register_img("./textures/rock.xpm");
		register_img("./textures/link_head.xpm");
		//walls
		register_img("./textures/walls/brick_red.xpm");
		register_img("./textures/walls/brick_white.xpm");
		register_img("./textures/walls/cinderblock.xpm");
		register_img("./textures/walls/roof_brick.xpm");
		register_img("./textures/walls/dlc2.xpm");
		//fonts
		register_img("./textures/fonts/monospace_ttf.xpm");
		split_image("/monospace_ttf.xpm", "monospace_", 32, 0);
		//render
		create_img((t_ui){1280, 720, 0},
			fill_img_color, "framework");
		create_img((t_ui){1280, 720, 0},
			fill_img_color, "framework_rev");
		//weapon
		register_img("./textures/weapon/M1911_idle_walk.xpm");
		i = split_image("/M1911_idle_walk.xpm", "M1911_walk_", 640, 0);
		cub->weapons[WPN_M1911].frame[WPN_FRAME_WALK] = i - 1;
		load_game_textures(cub, 0x00FFFF, 0xFF0000);
	}
}

//Setup Exemple
int	main(void)
{
	t_ml		*lx;
	t_cb		*cub;

	lx = gmlx(ACT_INIT);
	if (lx)
	{
		lx->purge_color = 0x030303;
		if (lx->set_win_size(1920, 1080) && lx->make_window("Ray of the Dead"))
		{
			cub = g_cub(ACT_INIT);
			if (cub)
			{
				lx->refresh = 0;
				register_xpm();			
				mlx_mouse_move(lx->ptr, lx->win, lx->width / 2, lx->height / 2);
				mlx_mouse_hide(lx->ptr, lx->win);
				mlx_hook(lx->win, KeyPress, (1L << 0), hook_keyboard, lx);
				mlx_hook(lx->win, MotionNotify, PointerMotionMask, mouse_move, cub);
				mlx_loop_hook(lx->ptr, display, lx);
				mlx_loop(lx->ptr);
			}
			lx->quit_window();
		}
	}
}
