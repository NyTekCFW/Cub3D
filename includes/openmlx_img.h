/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_img.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 06:08:03 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/28 00:06:52 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_IMG_H
# define OPENMLX_IMG_H

typedef struct ui_s
{
	int			x;
	int			y;
	int			w;
	int			h;
	__uint32_t	color;
}	t_ui;

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			bpp;
	int			len;
	int			endian;
	int			width;
	int			height;
	__uint32_t	size;
}	t_img;

typedef struct shader_s
{
	__uint32_t			file;
	int					created;
	int					is_stored;
	t_img				img;
	struct shader_s		*next;
}	t_shaders;

typedef struct texture_s
{
	t_shaders	shaders;
	__uint32_t	shaders_count;
}	t_texture;

void		create_img(t_ui ui, void (*func)(), char *name);
void		register_img(char *path);
void		print_img(t_vec2 pos, char *name);
void		purge_textures(void);
void		merge_img(t_shaders *d, t_shaders *b, t_vec2 u);
void		merge_img_overlay(t_img *d, t_img *b, t_vec2 u);
t_shaders	*get_img(char *name);
__uint32_t	blend_colors(__uint32_t bkg, __uint32_t frg, float alpha);
void		set_color(t_img *img, int adr, __uint32_t clr);
__uint32_t	get_px_color(t_img *img, t_vec2 xy);
__uint32_t	get_px_adr(t_img *img, t_vec2 xy);
void		fill_img_color(t_img *dest, __uint32_t color);
void		overlay_images(t_img *dest, t_img *bkg, t_img *frg, float alpha);
void		blitting_render(t_vec2 xs, t_vec2 dim, char *name);
int			split_image(char *name, char *output, int width, int i);
void		typewritter(char *str, t_vec2 v);
int			r_textheight(char *str);
int			r_textwidth(char *str);
void		export_img(char *name);
void		load_exported(char *name);
#endif