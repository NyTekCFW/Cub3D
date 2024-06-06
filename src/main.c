/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:05:05 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/06 06:29:02 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
/*
void	buffertest(t_img *img, t_ui ui)
{
	t_ml		*lx;
	t_shaders	*sh;
	__uint32_t	c;
	t_vec2		j;

	lx = gmlx(ACT_GET);
	j = (t_vec2){0, 0};
	if (lx)
	{
		sh = get_img("/brick_argb.xpm");
		if (sh)
		{
			while (j.y < ui.h)
			{
				j.x = 0;
				while (j.x < ui.w)
				{
					c = get_px_color(&sh->img, get_px_adr(&sh->img, j));
					set_color(img, get_px_adr(img, j), blend_colors(ui.color, c, 0.3));
					j.x++;
				}
				j.y++;
			}
		}
	}
}*/


int move = 0;

float px, py,pdx,pdy,pa;
int mapx=9, mapy=9, maps=64;
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

float degToRad(int a) { return a*PI/180.0;}
int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}

#define FOV 60

void drawrays3d(void)
{
	t_prim	p;
	t_prim	g;

	int r,mx,my,mp,dof; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
	
	g = ml_begin(ML_PRIM_POLYGON);
	
	ml_vertex(&g, (t_vec2){px,py});
	ra=FixAng(pa+30);//ray set back 30 degrees
	for(r=0;r<90;r++)
	{
	//---Vertical--- 
	dof=0; disV=100000;
	float Tan=tan(degToRad(ra));
	if(cos(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
	else if(cos(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
	else { rx=px; ry=py; dof=8;}                                                  //looking up or down. no hit  

	while(dof<8) 
	{ 
	mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapx+mx;                     
	if(mp>0 && mp<mapx*mapy && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
	else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
	} 
	vx=rx; vy=ry;

	//---Horizontal---
	dof=0; disH=100000;
	Tan=1.0/Tan; 
		if(sin(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;}//looking up 
	else if(sin(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;}//looking down
	else{ rx=px; ry=py; dof=8;}                                                   //looking straight left or right
	
	while(dof<8) 
	{ 
		mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapx+mx;                          
		if(mp>0 && mp<mapx*mapy && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
		else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
	}
	
	if(disV<disH){ rx=vx; ry=vy; disH=disV;}
	ml_vertex(&g, (t_vec2){rx,ry});

	int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
	int lineH = (maps*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
	int lineOff = 160 - (lineH>>1);           
	                                    //line offset
	if(disV<disH){ rx=vx; ry=vy; disH=disV; }
	ra=FixAng(ra-1); 


	p = ml_begin(ML_PRIM_QUADS);
	if (r == 0x008000)
	{
		ml_settexture(&p, "/brick_argb.xpm");
		ml_color(&p, 0x0000ff);
		ml_setintensity(&p, 0.2);
	}
	else
		ml_settexture(&p, "/ground.xpm");
	//ml_size(&p, 8);
	ml_vertex(&p, (t_vec2){r*8+600, lineOff + lineH});
	ml_vertex(&p, (t_vec2){r*8+600 + 8,lineOff + lineH});
	ml_vertex(&p, (t_vec2){r*8+600 + 8, lineOff});
	ml_vertex(&p, (t_vec2){r*8+600, lineOff});
	ml_setmode(&p, 0);
	ml_end(&p);                                                       //go to next ray
	}
	ml_color(&g, 0xFFFF00);
	ml_setmode(&g, 1);
	ml_size(&g, 2);
	ml_end(&g);
}


void draw_map2d()
{
	t_prim	c;
	int x,y,xo,yo;
	for(y = 0; y < mapy;y++)
	{
		for(x = 0; x < mapx;x++)
		{
			c = ml_begin(ML_PRIM_QUADS);
			xo=x*maps;
			yo=y*maps;
			ml_vertex(&c, (t_vec2){xo, yo});
			ml_vertex(&c, (t_vec2){xo, yo + maps});
			ml_vertex(&c, (t_vec2){xo + maps, yo + maps});
			ml_vertex(&c, (t_vec2){xo + maps, yo});
			ml_settexture(&c, "/ground.xpm");
			if (map[y*mapx+x] == 1) {ml_color(&c, 0xFFFFFF);} else ml_color(&c, 0);
			ml_setintensity(&c, 0.4);
			ml_end(&c);
		}
	}
}

int	display(t_ml *lx)
{
	if (lx->refresh)
	{
		lx->refresh = 0;

		lx->purge_window();
		generate_minimap();
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
			cub->player.mm_origin.x += (pdx * 5);
			cub->player.mm_origin.y += (pdy * 5);
			px += pdx * 5;
			py += pdy * 5;
		}
		else if (ks == XK_s)
		{
			cub->player.mm_origin.x -= (pdx * 5);
			cub->player.mm_origin.y -= (pdy * 5);
			px -= pdx * 5;
			py -= pdy * 5;
		}
		else if (ks == XK_a)
		{
			pa+=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
		}
		else if (ks == XK_d)
		{
			pa-=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
		}
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
		if (lx->set_win_size(1920, 1080) && lx->make_window("OpenMLX Showcase"))
		{
			get_porigin();
			register_img("./textures/brick_argb.xpm");
			register_img("./textures/ground.xpm");
			register_img("./textures/rock.xpm");
			register_img("./textures/link_head.xpm");
			px = 200;
			py = 220;
			pa=90;
			pdx=cos(degToRad(pa));
			pdy=-sin(degToRad(pa));
			lx->refresh = 0;
			mlx_loop_hook(lx->ptr, display, lx);
			mlx_hook(lx->win, KeyPress, (1L << 0), hook_keyboard, lx);
			mlx_loop(lx->ptr);
			while (1)
				;
			lx->quit_window();
		}
	}
}
