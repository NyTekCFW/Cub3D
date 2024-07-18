/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 06:59:52 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/17 07:59:16 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
/*
void draw_circle(float center_x, float center_y, float radius, __uint32_t color) {
    int num_segments = 40;
    float angle_increment = 2.0f * PI / num_segments;

    for (int i = 0; i < num_segments; ++i)
	{
		t_prim s = ml_begin(ML_PRIM_TRIANGLES);
        float theta1 = i * angle_increment;
        float theta2 = (i + 1) * angle_increment;

        t_vec2 p0 = {center_x, center_y}; // Centre du cercle
        t_vec2 p1 = {center_x + radius * cosf(theta1), center_y + radius * sinf(theta1)};
        t_vec2 p2 = {center_x + radius * cosf(theta2), center_y + radius * sinf(theta2)};

        ml_color(&s, color);
        ml_vertex(&s, p0);
        ml_vertex(&s, p1);
        ml_vertex(&s, p2);
		//ml_setmode(&s, ML_MODE_LINE);
		ml_size(&s, 1);
		ml_savemesh(&s, get_img("record_logo"));
		ml_end(&s);
    }
}

void	_draw_bkg(t_ml *lx)
{
	t_prim		s;

	if (lx)
	{
		s = ml_begin(ML_PRIM_QUADS);
		ml_vertex(&s, (t_vec2){0, 0});
		ml_vertex(&s, (t_vec2){150, 0});
		ml_vertex(&s, (t_vec2){150, 60});
		ml_vertex(&s, (t_vec2){0, 60});
		ml_color(&s, 0x030303);
		create_img_mesh(&s, "record_logo");
		draw_circle(30, 30, 17, 0xFF0000);
		typewritter("record_logo", "Rec", (t_vec2){50, 15});
		typewritter("record_logo", ".", (t_vec2){50 + r_textwidth("Rec"), 23});
		export_img("record_logo");
		exit(1);
	}
}

/// @brief display a image
/// @param name 
void	draw_record(char *name)
{
	t_ml	*lx;
	t_prim	s;

	lx = gmlx(ACT_GET);
	if (lx)
	{
		
	}
}
*/