/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:05:05 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/14 09:56:44 by lchiva           ###   ########.fr       */
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


int	hand_count(int z)
{
	static int	b = 0;

	if (b == 0)
		b = z;
	return (b);
}

void	register_hands(void)
{
	int	i;

	i = 0;
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
	hand_count(i);
}

void	draw_hand(t_ml *lx)
{
	static int	v = 0;
	static int	b = 0;
	char		m[15];

	xmemcpy(m, "hand_anim_000\0", 15);
	m[10] = 0x30 + (b / 100);
	m[11] = 0x30 + ((b / 10) % 10);
	m[12] = 0x30 + (b % 10);
	buffer_img(get_img("framework"), get_img(m), (t_vec2){(lx->width / 2) - 320, (lx->height - 400 )});
	if (v == 0 && b <= hand_count(0))
	{
		b++;
		usleep(8000);
		return ;
	}
	v = 1;
	if (v == 1 && b >= 0)
	{
		b--;
		usleep(8000);
		return ;
	}
	v = 0;
}
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

int	spacing(char c)
{
	if (c >=  '0' && c <= '9')
		return (17);
	else if (c >= 'a' && c <= 'z')
		return (16);
	else if (c == ' ')
		return (8);
	return (19);
}

void	typewritter(char *str, t_vec2 v)
{
	size_t	i;
	char	m[17];
	int		c;

	i = 0;
	while (str[i])
	{
		c = 0;
		xmemcpy(m, "\0", 17);
		if (str[i] >= '!' && str[i] <= '~')
		{
			xmemcpy(m, "monospace_000\0", 17);
			c = 0x21;
		}
		m[11] = 0x30 + (((str[i] - c) / 10) % 10);
		m[12] = 0x30 + ((str[i] - c) % 10);
		buffer_img(get_img("framework"), get_img(m),
			(t_vec2){v.x, v.y});
		v.x += spacing(str[i]);
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
		//lx->refresh = 0;
		//lx->purge_window();
		//print_img((t_vec2){0, 0}, "skybox_cub3d");
		//print_img((t_vec2){0, 0}, "icon_minimap");
		//t_players f;
		//	init_player(&f);
		//return ;
		raycasting();
		build_weapon(lx);
		buffer_img(get_img("framework"), get_img("icon_minimap"), (t_vec2){0, 0});
		typewritter("Hold F to open [Cost: 4000$]", (t_vec2){0, 300});
		draw_hand(lx);
		print_img((t_vec2){0, 0}, "framework");
		
		//draw_cone();
		//generate_minimap();
		//drawplayer();
	//	drawrays3d();
		//move = 0;
	}
	return (1);
}

int	check_move(t_cb *cub, t_vec2 v)
{
	if (v.x >= 0 && v.x < cub->map_data.width)
	{
		if (v.y >= 0 && v.y < cub->map_data.height)
			return (1);
	}
	return (0);
}

void move_forward(t_cb *cub)
{
	t_vec2		v;
	t_player	*player;

	player = &cub->player;
	v = (t_vec2){(int)(player->origin.x + player->dir.x * 0.1)
		/ cub->map_data.envdist, (int)(player->origin.y)
		/ cub->map_data.envdist};
	if (check_move(cub, v) && cub->map_data.map[v.y][v.x] == '0')
		player->origin.x += player->dir.x * 0.1;
	v = (t_vec2){(int)(player->origin.x) / cub->map_data.envdist,
		(int)(player->origin.y + player->dir.y * 0.1)
		/ cub->map_data.envdist};
	if (check_move(cub, v) && cub->map_data.map[v.y][v.x] == '0')
		player->origin.y += player->dir.y * 0.1;
}
/*
void move_backward(t_cb *cub)
{
	t_vec2		v;
	t_player	*player;

	player = &cub->player;
	v = (t_vec2){(int)(player->origin.x - player->dir.x * 0.1)
		/ cub->map_data.envdist,
		(int)(player->origin.y / cub->map_data.envdist)};
	if (check_move(cub, v) && cub->map_data.map[v.y][v.x] == '0')
		player->origin.x -= player->dir.x * 0.1;
	v = (t_vec2){(int)(player->origin.x) / cub->map_data.envdist,
		(int)(player->origin.y - player->dir.y * 0.1)};
	if (check_move(cub, v) && cub->map_data.map[v.y][v.x] == '0')
		player->origin.y -= player->dir.y * 0.1;
}


void hide_cursor(void)
{
    Pixmap no_data;
    XColor black;
    static char empty[] = {0};
    Cursor cursor;

    black.red = black.green = black.blue = 0;

    no_data = XCreateBitmapFromData(app->display, app->window, empty, 1, 1);
    cursor = XCreatePixmapCursor(app->display, no_data, no_data, &black, &black, 0, 0);
    XDefineCursor(app->display, app->window, cursor);
    XFreeCursor(app->display, cursor);
    XFreePixmap(app->display, no_data);
}
*/
void	move_backward(t_cb *cub)
{
	t_player	*player;

	player = &cub->player;
	if (cub->map_data.map[(int)(player->origin.y / cub->map_data.envdist)][(int)(player->origin.x - player->dir.x * 0.1 / cub->map_data.envdist)] == '0')
		player->origin.x -= player->dir.x * 0.1;
	if (cub->map_data.map[(int)((player->origin.y - player->dir.y * 0.1) / cub->map_data.envdist)][(int)(player->origin.x)] == '0')
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
	/*else if (keycode == XK_y)
		cub->player.vangle += 0.1;//1.5max
	else if (keycode == XK_u)
		cub->player.vangle -= 0.1;//-0.8max*/
	//else if (keycode == XK_v)
	//	cub->player.weapon.ammo_clip -= 1;
	lx->refresh = 1;
	move = 1;
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
			if (player->vangle > 1.5)
				player->vangle = 1.5;
			if (player->vangle < -0.8)
				player->vangle = -0.8;
			last = (t_vec2){lx->width / 2, lx->height / 2};
			printf("%i %i\n", x, y);
			lx->refresh = 1;
		}
		if (x != lx->width / 2 || y != lx->height / 2)
			mlx_mouse_move(lx->ptr, lx->win,
				lx->width / 2, lx->height / 2);
	}
	return (0);
}

/*
int mouse_move(int x, int y, t_cb *cub)
{
    static int last_x = -1;
    static int last_y = -1;

    if (last_x == -1 || last_y == -1)
    {
        last_x = x;
        last_y = y;
        return (0);
    }

    int delta_x = x - last_x;
    int delta_y = y - last_y;

    // Ajuste l'angle horizontal
    double rot_speed = 0.002; // Ajustez cette valeur pour la sensibilité de la souris
    double rot = delta_x * rot_speed;

    t_player *player = &cub->player;
    double old_dir_x = player->dir.x;
    player->dir.x = player->dir.x * cos(-rot) - player->dir.y * sin(-rot);
    player->dir.y = old_dir_x * sin(-rot) + player->dir.y * cos(-rot);
    double old_plane_x = player->plane.x;
    player->plane.x = player->plane.x * cos(-rot) - player->plane.y * sin(-rot);
    player->plane.y = old_plane_x * sin(-rot) + player->plane.y * cos(-rot);

    // Ajuste l'angle vertical (inversé)
    player->vangle -= delta_y * rot_speed;
    if (player->vangle > MAX_VERTICAL_ANGLE)
        player->vangle = MAX_VERTICAL_ANGLE;
    if (player->vangle < MIN_VERTICAL_ANGLE)
        player->vangle = MIN_VERTICAL_ANGLE;

    last_x = cub->win_width / 2;
    last_y = cub->win_height / 2;

    // Recentrer la souris
    mlx_mouse_move(cub->win, last_x, last_y);

    return (0);
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
		buffer_img(get_img("framework"), get_img(m), (t_vec2){320, 400});
		print_img((t_vec2){320, 400}, "framework");
		usleep(8000);
		b++;
	}
	while (b >= 0)
	{
		m[10] = 0x30 + (b / 100);
		m[11] = 0x30 + ((b / 10) % 10);
		m[12] = 0x30 + (b % 10);
		buffer_img(get_img("framework"), get_img(m), (t_vec2){320, 400});
		print_img((t_vec2){320, 400}, "framework");
		usleep(8000);
		b--;
	}
}*/
int	mouse_click(int button, int x, int y, t_cb *cub)
{
    (void)x;
    (void)y;
    t_ml *lx = gmlx(0);
    
    if (lx && cub)
	{
        //Assurez-vous que la fenêtre garde le focus lors du clic
        //mlx_mouse_move(lx->ptr, lx->win, lx->width / 2, lx->height / 2);
        lx->refresh = 1;
    }
    printf("Mouse button %d clicked at (%d, %d)\n", button, x, y);
    return -1;
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
			register_img("./textures/fonts/monospace_ttf.xpm");
		//	register_img("./textures/fonts/digits.xpm");
		//	register_img("./textures/fonts/alpha_upper.xpm");
		//	register_img("./textures/fonts/alpha_lower.xpm");
			register_img("./textures/link_head.xpm");
			split_image("/monospace_ttf.xpm", "monospace_", 32, 0);
		//	split_image("/alpha_upper.xpm", "uletter_", 25, 0);
		//	split_image("/alpha_lower.xpm", "lletter_", 25, 0);
			lx->refresh = 0;
			build_images();
			//build_minimap();
			
		//	sleep(4);
			register_hands();
			
			mlx_mouse_move(lx->ptr, lx->win, lx->width / 2, lx->height / 2);
			mlx_hook(lx->win, KeyPress, (1L << 0), hook_keyboard, lx);
			mlx_hook(lx->win, MotionNotify, PointerMotionMask, mouse_move, cub);
			mlx_loop_hook(lx->ptr, display, lx);
			mlx_loop(lx->ptr);
			lx->quit_window();
		}
	}
}
//https://smallseotools.com/text-to-image/