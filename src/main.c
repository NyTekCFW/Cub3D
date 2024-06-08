/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:05:05 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/08 20:41:06 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int move = 0;

double px, py,pdx,pdy,pa;
int mapx=9, mapy=9, maps=32;
int cell_size = 21;
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
void drawrays3d(void)
{
    t_prim p;
    t_prim g;

    int r, mx, my, mp, dof;
    double vx, vy, rx, ry, ra, xo, yo, disV, disH;

    g = ml_begin(ML_PRIM_POLYGON);
    ml_vertex(&g, (t_vec2){px, py});
    ra = FixAng(pa + 30); // ray set back 30 degrees

    for (r = 0; r < 90; r++)
    {
        // --- Vertical ---
        dof = 0;
        disV = 100000;
        double Tan = tan(degToRad(ra));

        if (cos(degToRad(ra)) > 0.001)
        {
            rx = (((int)px / cell_size) * cell_size) + cell_size;
            ry = (px - rx) * Tan + py;
            xo = cell_size;
            yo = -xo * Tan;
        }
        else if (cos(degToRad(ra)) < -0.001)
        {
            rx = (((int)px / cell_size) * cell_size) - 0.0001;
            ry = (px - rx) * Tan + py;
            xo = -cell_size;
            yo = -xo * Tan;
        }
        else
        {
            rx = px;
            ry = py;
            dof = 8;
        } // looking up or down. no hit

        while (dof < 8)
        {
            mx = (int)(rx) / cell_size;
            my = (int)(ry) / cell_size;
            mp = my * mapx + mx;
            if (mp > 0 && mp < mapx * mapy && map[mp] == 1)
            {
                dof = 8;
                disV = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py);
            } // hit
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            } // check next horizontal
        }
        vx = rx;
        vy = ry;

        // --- Horizontal ---
        dof = 0;
        disH = 100000;
        Tan = 1.0 / Tan;
        if (sin(degToRad(ra)) > 0.001)
        {
            ry = (((int)py / cell_size) * cell_size) - 0.0001;
            rx = (py - ry) * Tan + px;
            yo = -cell_size;
            xo = -yo * Tan;
        }
        else if (sin(degToRad(ra)) < -0.001)
        {
            ry = (((int)py / cell_size) * cell_size) + cell_size;
            rx = (py - ry) * Tan + px;
            yo = cell_size;
            xo = -yo * Tan;
        }
        else
        {
            rx = px;
            ry = py;
            dof = 8;
        } // looking straight left or right

        while (dof < 8)
        {
            mx = (int)(rx) / cell_size;
            my = (int)(ry) / cell_size;
            mp = my * mapx + mx;
            if (mp > 0 && mp < mapx * mapy && map[mp] == 1)
            {
                dof = 8;
                disH = cos(degToRad(ra)) * (rx - px) - sin(degToRad(ra)) * (ry - py);
            } // hit
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            } // check next horizontal
        }

        if (disV < disH)
        {
            rx = vx;
            ry = vy;
            disH = disV;
        }
        ml_vertex(&g, (t_vec2){rx, ry});

        int ca = FixAng(pa - ra);
        disH = disH * cos(degToRad(ca)); // fix fisheye
        int lineH = (cell_size * 200) / (disH);
        if (lineH > 200) { lineH = 200; } // line height and limit
        int lineOff = 160 - (lineH >> 1); // line offset

        if (disV < disH)
        {
            rx = vx;
            ry = vy;
            disH = disV;
        }
        ra = FixAng(ra - 1);

        p = ml_begin(ML_PRIM_QUADS);
        if (r == 0x008000)
        {
            ml_settexture(&p, "/brick_argb.xpm");
            ml_color(&p, 0x0000ff);
            ml_setintensity(&p, 0.2);
        }
        else
        {
            ml_settexture(&p, "/ground.xpm");
        }
        ml_vertex(&p, (t_vec2){r * 14, 200 + lineOff + lineH});
        ml_vertex(&p, (t_vec2){r * 14 + 14, 200 + lineOff + lineH});
        ml_vertex(&p, (t_vec2){r * 14 + 14, 200 + lineOff});
        ml_vertex(&p, (t_vec2){r * 14, 200 + lineOff});
        ml_setmode(&p, 0);
        ml_end(&p); // go to next ray
    }
    ml_color(&g, 0xFFFF00);
    ml_setmode(&g, 1);
    ml_size(&g, 1);
    ml_end(&g);
}



int	display(t_ml *lx)
{
	if (lx->refresh)
	{
		lx->refresh = 0;

		lx->purge_window();
		print_img((t_vec2){0, 0}, "skybox_cub3d");
		print_img((t_vec2){0, 0}, "icon_minimap");
		//generate_minimap();
		//drawplayer();
		drawrays3d();
		move = 0;
	}
	return (1);
}

static int	hook_keyboard(int ks, t_ml *lx)
{
	t_cb	*cub;

	cub = g_cub(ACT_GET);
	if (cub)
	{
		if (ks == XK_w)
		{
			cub->player.origin.x += cub->player.pad.x;
			cub->player.origin.y += cub->player.pad.y;
			px+=pdx*5; py+=pdy*5;
		}
		else if (ks == XK_s)
		{
			cub->player.origin.x -= cub->player.pad.x;
			cub->player.origin.y -= cub->player.pad.y;
			px-=pdx*5; py-=pdy*5;
		}
		else if (ks == XK_a)
		{
			pa+=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
			cub->player.angle -= 0.1;
			if (cub->player.angle <= 0)
				cub->player.angle += (PI * 2);
		}
		else if (ks == XK_d)
		{
			pa-=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
			cub->player.angle += 0.1;
			if (cub->player.angle >= (PI * 2))
				cub->player.angle -= (PI * 2);
		}
		cub->player.pad.x = cos(cub->player.angle) * 5;
		cub->player.pad.y = sin(cub->player.angle) * 5;
		printf("angle = %f\n", cub->player.angle);
	}
	lx->refresh = 1;
	move = 1;
	return (1);
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
			mlx_loop_hook(lx->ptr, display, lx);
			mlx_hook(lx->win, KeyPress, (1L << 0), hook_keyboard, lx);
			mlx_loop(lx->ptr);
			while (1)
				;
			lx->quit_window();
		}
	}
}
