/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:28:48 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/18 14:13:27 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char *_find_color(char *trim)
{
	size_t	i;
	size_t	j;
	char	b[13];

	i = 0;
	j = 0;
	xmemset(b, 0, 13);
	while (trim[i])
	{
		if ((trim[i] >= '0' && trim[i] <= '9') || trim[i] == ' '
			 || trim[i] == '	' || trim[i] == ',')
		{
			if (j < 13 && trim[i] != '	' && trim[i] != ' ')
				b[j++] = trim[i];
		}
		else
			break ;
		i++;
	}
	b[j] = 0;
	xfree((void **)&trim);
	return (xstrdup(b));
}

char	*find_color(t_file *file, char *v)
{
	int			u;
	char		*p;
	char		*d;

	if (!file || !file->content || !file->map)
		return (NULL);
	u = 0;
	while (u < file->total_line + 1 && file->map[u])
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
						printf("Error: Multiple %s color found\n", v);
						return (NULL);
					}
				}
				u++;
			}
			p += xstrlen(v);
			return (_find_color(xstrtrim(p)));
		}
		u++;
	}
	return (NULL);
}

/*
while (++start < end && file->map[start])
	{
		i = -1;
		while (file->map[start][++i])
		{
			c = file->map[start][i];
			if (c == '\n')
			{
				i = -2;
				break ;
			}
			else if (c == ' ' || c == '	' || (c >= '0' && c <= '9'))
				continue ;
			else
			{
				i = -1;
				break ;
			}
		}
		if (i != -1 && i != -2)
		{
			printf("start = %i\n", start);
			break ;
		}
	}
*/


void	find_map_start(t_file *file, int *start, int end, int *i)
{
	char	c;

	while (++(*start) < end && file->map[*start])
	{
		*i = -1;
		while (file->map[*start][++(*i)])
		{
			c = file->map[*start][*i];
			if (c == '\n')
			{
				*i = -2;
				break ;
			}
			else if (c == ' ' || c == '	' || (c >= '0' && c <= '9'))
				continue ;
			else
			{
				*i = -1;
				break ;
			}
		}
		if (*i != -1 && *i != -2)
			break ;
	}
}


void	find_map_end(t_file *file, int start, int *end, int *i)
{
	char	c;

	while (--(*end) > start && file->map[*end])
	{
		*i = -1;
		while (file->map[*end][++(*i)])
		{
			c = file->map[*end][*i];
			if (c == '\n')
			{
				*i = -2;
				break ;
			}
			else if (c == ' ' || c == '	' || (c >= '0' && c <= '9'))
				continue ;
			else
			{
				*i = -1;
				break ;
			}
		}
		if ((*i != -1 && *i != -2 )|| *i == -1)
			break ;
	}
}

void	check_sym_map(t_file *file, int start, int end)
{
	char	c;
	int		i;

	start -= 1;
	while (++start <= end && file->map[start])
	{
		i = -1;
		while (file->map[start][++i])
		{
			c = file->map[start][i];
			if (c == ' ' || c == '	' || c == '0' || c == '1' || c == 'N'
				|| c == 'W' || c == 'S' || c == 'E')
			{
				printf("%c", c);
				continue ;
			}
			else
				return ;
		}
		printf("\n");
	}
	printf("map is valid\n");
}

void	parse_map(t_file *file)
{
	int		end;
	int		start;
	int		i;

	end = file->total_line;
	start = -1;
	i = -1;
	if (!file || !file->content || !file->map)
		return ;
	find_map_start(file, &start, end, &i);
	if (i == -1 || i == -2)
		return ;
	i = -1;
	find_map_end(file, start, &end, &i);
	if (i == -1 || i == -2)
		return ;
	printf("start at = %i - end at = %i\n", start, end);
	check_sym_map(file, start, end);
}

void	check_player()
{

}
