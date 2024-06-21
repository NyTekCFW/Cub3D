/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:15:01 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/20 09:22:05 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
/*
void	flashlight(t_shaders *sh, t_ray *ray, t_vec2 v, __uint32_t c)
{
	t_ml	*lx;
	double	xdist;
	t_vec2f	center;
	t_vec2f	vf;
	double	a;

	lx = gmlx(ACT_GET);
	if (lx && sh)
	{
		center = (t_vec2f){sh->img.width / 2, sh->img.height / 2};
		vf = (t_vec2f){v.x, v.y};
		xdist = dist(center, vf);
		if (xdist <= 85.0 + ray->pwall_dist)
		{
			a = exp(-0.05 * xdist) + (0.8 / (ray->pwall_dist + 1));
			if (xdist > 85.0)
				a *= 1.0 - (xdist - 85.0) / (85.0 / 2.0);
			a = fmax(0.0, fmin(a, 1.0));
			set_color(&sh->img, get_px_adr(&sh->img, v), blend_colors(c, 0xffffff, a));
		}
	}
}

int	get_texture_color(t_img *texture, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0); // return a default color or handle out-of-bounds error
	pixel = texture->addr + (y * texture->len + x * (texture->bpp / 8));
	color = *(int *)pixel;
	return (color);
}

void	draw_floor_and_ceiling(t_ray *ray, t_player *p, t_shaders *sh, int x, int screenHeight)
{
	t_shaders	*cl;
	t_shaders	*gr;
	int y;
	int pX = p->origin.x;
	int pY = p->origin.y;
	double dirX0 = p->dir.x - p->plane.x;
	double dirY0 = p->dir.y - p->plane.y;
	double dirX1 = p->dir.x + p->plane.x;
	double dirY1 = p->dir.y + p->plane.y;


	cl = get_img("/ground.xpm");
	gr = get_img("/ground.xpm");
	for (y = ray->draw_end; y < screenHeight; y++)
	{
		// Current distance from the player to the floor
		double posZ = 0.5 * screenHeight;
		double rowDistance = posZ / (y - screenHeight / 2 + (screenHeight / 2) * tan(p->vangle));

		// Calculate the real world step vector we have to add for each x (parallel to the camera plane)
		double floorStepX = rowDistance * (dirX1 - dirX0) / screenHeight;
		double floorStepY = rowDistance * (dirY1 - dirY0) / screenHeight;

		// Real world coordinates of the leftmost column (this is the start point)
		double floorX = pX + rowDistance * dirX0;
		double floorY = pY + rowDistance * dirY0;

		int tx, ty;
		(void)x;
		// Loop through all columns
		//for (int xFloor = 0; xFloor < screenHeight; ++xFloor)
	//	{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			tx = (int)(gr->img.width * (floorX - cellX)) & (gr->img.width - 1);
			ty = (int)(gr->img.height * (floorY - cellY)) & (gr->img.height - 1);


			// choose texture and draw the pixel
			int color = get_texture_color(&gr->img, tx, ty);
			set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), color);

			posZ = 0.5 * screenHeight ;
		 rowDistance = (posZ / (y - screenHeight / 2 + (screenHeight / 2) ));

		// Calculate the real world step vector we have to add for each x (parallel to the camera plane)
		 floorStepX = rowDistance * (dirX1 - dirX0) / screenHeight;
	 floorStepY = rowDistance * (dirY1 - dirY0) / screenHeight;

		// Real world coordinates of the leftmost column (this is the start point)
		 floorX = pX + rowDistance * dirX0;
		 floorY = pY + rowDistance * dirY0;
		 
		 cellX = (int)(floorX);
			cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			tx = (int)(gr->img.width * (floorX - cellX)) & (gr->img.width - 1);
			ty = (int)(gr->img.height * (floorY - cellY)) & (gr->img.height - 1);

			floorX += floorStepX;
			floorY += floorStepY;
			// Repeat for ceiling
			color = get_texture_color(&cl->img, tx, ty);
			set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, screenHeight - y - 1}), color);
	//	}
	}
}

t_vec2	step_cell(t_player *p, t_vec3 u, t_shaders *sh)
{
	t_vec2	s;
	t_vec2f	dir0;
	t_vec2f	floor;
	t_vec2	t;
	double	row;

	s = (t_vec2){(int)p->origin.x, (int)p->origin.y};
	dir0 = (t_vec2f){p->dir.x - p->plane.x, p->dir.y - p->plane.y};
	row = ((0.5 * u.z) / (u.y - u.z / 2 + (u.z / 2)) * tan(p->vangle));//tan(p->vangle)
	floor = (t_vec2f){s.x + row * dir0.x, s.y + row * dir0.y};
	t = (t_vec2){(int)(sh->img.width * (floor.x - (int)floor.x)) & (sh->img.width - 1),
				(int)(sh->img.height * (floor.y - (int)floor.y)) & (sh->img.height - 1)};
	return (t);
}

void	draw_line(int x, t_ray *ray, t_player *p)
{
	t_shaders	*sh;
	t_shaders	*cl;
	t_vec2		cell;
	int			y;

	sh = get_img("framework");
	cl = get_img("/brick_argb.xpm");
	//ceiling
	y = ray->draw_start - 1;
	while (y >= 0)
	{
		cell = step_cell(p, (t_vec3){x, y, sh->img.height}, cl);
		int color = get_px_color(&cl->img, cell);
		//get_texture_color(&cl->img, tx, ty);
		set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), blend_colors(color, 0x030303, (float)y / (float)ray->draw_end));
		if (p->flashlight == 1) 
			flashlight(sh, ray, (t_vec2){x, y}, color);
		y--;
	}
	//floor render
	y = sh->img.height - 1;
	while (y >= ray->draw_end)
	{
		set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), blend_colors(0x00ff00, 0x030303, 1 - ((float)y / (float)sh->img.height)));
		if (p->flashlight == 1)
			flashlight(sh, ray, (t_vec2){x, y}, 0x00ff00);
		y--;
	}
	//wall render
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		set_color(&sh->img, get_px_adr(&sh->img, (t_vec2){x, y}), blend_colors(ray->color, 0x030303, ray->pwall_dist / 15));
		if (p->flashlight == 1)
			flashlight(sh, ray, (t_vec2){x, y}, ray->color);
		y++;
	}
//	draw_floor_and_ceiling(ray, p, sh, x, sh->img.height);
}

void	ray_dda(t_ray *ray, t_cb *cub, t_ml *lx)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (check_move(cub, (t_vec2){ray->map.x / cub->map_data.envdist,
			ray->map.y / cub->map_data.envdist})
		&& cub->map_data.map[ray->map.y / cub->map_data.envdist]
		[ray->map.x / cub->map_data.envdist] > '0')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->pwall_dist = (ray->map.x - cub->player.origin.x
				+ (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->pwall_dist = (ray->map.y - cub->player.origin.y
				+ (1 - ray->step.y) / 2) / ray->dir.y;
	ray->line_height = (int)(lx->height / ray->pwall_dist);
}

void	ray_step(t_ray *ray, t_cb *cub)
{
	t_player	*player;

	player = &cub->player;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->origin.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x
			= (ray->map.x + 1.0 - player->origin.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->origin.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y
			= (ray->map.y + 1.0 - player->origin.y) * ray->delta_dist.y;
	}
}

void	init_ray(t_ray *ray, t_ml *lx, t_cb *cub, int x)
{
	t_player	*player;

	player = &cub->player;
	ray->camera = (2 * x) / (double)lx->width - 1;
	ray->dir.x = player->dir.x + player->plane.x * ray->camera;
	ray->dir.y = player->dir.y + player->plane.y * ray->camera;
	ray->map = (t_vec2){(int)player->origin.x, (int)player->origin.y};
	ray->delta_dist = (t_vec2f){fabs(1 / ray->dir.x), fabs(1 / ray->dir.y)};
	ray->hit = 0;
	ray_step(ray, cub);
	ray_dda(ray, cub, lx);
	ray->draw_start = (-ray->line_height / 2) + (lx->height / 2) + ((lx->height / 2) * tan(player->vangle));
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (lx->height / 2) + ((lx->height / 2) * tan(player->vangle));
	if (ray->draw_end >= lx->height)
		ray->draw_end = lx->height - 1;
	if (ray->side == 0)
	{
		if (ray->dir.x < 0)//WEST
			ray->color = 0xFF0000;
		else//EST
			ray->color = 0xFFFF00;
	}
	else
	{
		if (ray->dir.y > 0)//SOUTH
			ray->color = 0x00FFFF;
		else//NORTH
			ray->color = 0xFF00FF;
	}
	if (ray->draw_end >= 0 && ray->draw_end < lx->height)
		draw_line(x, ray, player);
}

void	raycast_env(void)
{
	t_ray	ray;
	t_cb	*cub;
	t_ml	*lx;
	int		x;

	lx = gmlx(ACT_GET);
	cub = g_cub(ACT_GET);
	x = 0;
	xmemset(&ray, 0, sizeof(t_ray));
	if (lx && cub)
	{
		fill_img_color(&get_img("framework")->img, 0);
		while (x < lx->width)
		{
			init_ray(&ray, lx, cub, x);
			x++;
		}
	}
}*/