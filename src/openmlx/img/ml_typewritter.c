/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_typewritter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:58:38 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/20 08:35:10 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/openmlx.h"

static int	font_spacing(char c)
{
	if (c >= '0' && c <= '9')
		return (17);
	else if (c >= 'a' && c <= 'z')
	{
		if (c == 'w')
			return (21);
		else
			return (17);
	}
	else if (c == ' ')
		return (8);
	if (c == 'W')
		return (24);
	return (19);
}

int	r_textwidth(char *str)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (str[i])
	{
		w += font_spacing(str[i]);
		i++;
	}
	return (w);
}

int	r_textheight(char *str)
{
	int	i;
	int	w;

	i = 0;
	w = 26;
	while (str[i])
	{
		if (str[i] == '\n')
			w += 26;
		i++;
	}
	return (w);
}

void	typewritter(char *str, t_vec2 v)
{
	size_t	i;
	char	m[17];
	int		c;

	i = 0;
	c = v.x;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			v = (t_vec2){c, v.y + 26};
			i++;
			continue ;
		}
		xmemcpy(m, "\0", 17);
		if (str[i] >= '!' && str[i] <= '~')
			xmemcpy(m, "monospace_000\0", 17);
		m[11] = 0x30 + (((str[i] - 0x21) / 10) % 10);
		m[12] = 0x30 + ((str[i] - 0x21) % 10);
		merge_img(get_img("framework"), get_img(m), v);
		v.x += font_spacing(str[i]);
		i++;
	}
}
