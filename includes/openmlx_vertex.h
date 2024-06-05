/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_vertex.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:23:13 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/02 12:40:32 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct prim_s
{
	int			primitive;
	t_vec2		point[360];
	int			cpoint;
	__uint32_t	size;
	int			mode;
	int			uv;
	int			wrapping;
	int			texture;
	t_img		*img;
	float		intensity;
	__uint32_t	color_texture;
	__uint32_t	color;
}	t_prim;

int		is_valid_color(__uint32_t c);
t_prim	ml_begin(int prim);
void	ml_vertex(t_prim *s, t_vec2 origin);
void	ml_color(t_prim *s, __uint32_t color);
void	ml_size(t_prim *s, __uint32_t size);
void	ml_setmode(t_prim *s, int mode);
void	ml_settexture(t_prim *s, char *name);
void	ml_setintensity(t_prim *s, float i);
void	ml_setuv(t_prim *s, int uv);
void	ml_setwrap(t_prim *s, int wrap);
void	ml_end(t_prim *s);
void	ml_put_pixel(int x, int y, __uint32_t color);
void	ml_draw_points(t_prim *s);
void	ml_draw_lines(t_prim *s, int w, int e);
void	ml_draw_line_sl(t_prim *s);
void	ml_draw_triangles(t_prim *s);
void	ml_draw_quads(t_prim *s);
void	ml_draw_quad_strip(t_prim *s);
void	ml_draw_polygon(t_prim *s);
int		ml_can_draw(t_prim *s, t_vec2 xy);