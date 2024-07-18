/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:40:56 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/18 12:10:24 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*find_texture(t_file *file, char *v)
{
	int			u;
	char		*p;
	char		*d;

	if (!file || !file->content || !file->map)
		return (NULL);
	u = 0;
	while (file->map[u])
	{
		p = xstrstr(file->map[u], v);
		if (p)
		{
			u++;
			while (file->map[u])
			{
				if (file->map[u])
				{
					d = xstrstr(file->map[u], v);
					if (d)
					{
						printf("Error: Multiple %s texture found\n", v);
						return (NULL);
					}
				}
				u++;
			}
			p = xstrstr(p, "./textures/walls/");
			return (xstrtrim(p));
		}
		u++;
	}
	return (NULL);
}

static int	_check_alloc(t_file *file, char *line, int *i)
{
	int	a;

	a = 0;
	xfree((void **)&line);
	if (file && file->map)
	{
		while (a < *i + 1)
		{
			if (!file->map[a])
			{
				a = *i + 1;
				while (--a >= 0)
					xfree((void **)&file->map[a]);
				xfree((void **)&file->map);
				*i = file->total_line + 1;
				return (0);
			}
			a++;
		}
		return (1);
	}
	return (0);
}


int	fill_file_map(t_file *file)
{
	int		i;
	char	*line;

	if (!file || !file->content)
		return (0);
	i = -1;
	line = NULL;
	file->total_line = get_total_line(file);
	file->pos = file->content;
	if (xalloc((void **)&file->map, sizeof(char *), file->total_line + 1))
	{
		while (++i < file->total_line + 1)
		{
			line = get_next_line(file);
			if (line)
			{
				printf("<%s>\n", line);
				file->map[i] = xstrdup(line);
				if (!_check_alloc(file, line, &i))
					return (0);
			}
			else
				file->map[i] = NULL;
		}
		return (1);
	}
	return (0);
}
