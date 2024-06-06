/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 06:24:55 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/06 06:35:41 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int smapx=9, smapy=9, smaps=64;
int smap[] =
{
	1,1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,1,
	1,0,1,0,0,0,0,0,1,
	1,0,0,0,4,0,0,0,1,
	1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,
};

void	draw_cone(void)
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

}