/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:10:44 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/18 07:57:09 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static size_t	_get_cub_size(char *av)
{
	char	c;
	size_t	len;
	int		fd;

	fd = open(av, O_RDONLY);
	len = 0;
	c = 0;
	if (fd > 0)
	{
		while (read(fd, &c, 1) > 0)
			len++;
		close(fd);
	}
	return (len);
}

static void	_initdata(t_file *f, char *file)
{
	if (f)
	{
		f->content = file;
		f->pos = file;
		f->total_line = 0;
		f->map = NULL;
	}
}

int	check_file(char *av)
{
	size_t	len;
	ssize_t	r;
	int		fd;
	t_cb	*cub;
	char	*file;

	len = _get_cub_size(av);
	fd = open(av, O_RDONLY);
	cub = g_cub(ACT_GET);
	if (len > 0 && fd > 0 && cub)
	{
		if (xalloc((void **)&file, len + 1, sizeof(char)))
		{
			r = read(fd, file, len);
			file[len] = '\0';
			_initdata(cub->map_data.file, file);
			close(fd);
			(void)r;
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	check_arg(int argc, char **argv)
{
	char	*format;

	if (argc != 2)
	{
		printf("Error\n%i instead 1 arguments\n", argc - 1);
		printf("Ex : ./cub3d maps/<map>.cub\n");
		return (0);
	}
	format = xstrrchr(argv[1], '.');
	if (format)
	{
		if (!xstrcmp(format, ".cub"))
			return (1);
	}
	printf("Error : Invalid map format\n");
	return (0);
}
