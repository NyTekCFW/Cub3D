/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_string_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 09:19:11 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/29 03:36:42 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

char	*xstrcpy(char *buffer, const char *src)
{
	size_t	i;

	i = 0;//xstrlen(src);
	//smo_copy(buffer, src, i + 1);
	while (src[i])
	{
		buffer[i] = src[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

void	xwrite(int fd, const void *data, size_t n)
{
	ssize_t	p;

	p = write(fd, data, n);
	if (p != (long)n)
		p = write(STDERR_FILENO, "write error\n", 12);
}
