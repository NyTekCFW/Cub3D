/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_string_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 09:19:11 by lchiva            #+#    #+#             */
/*   Updated: 2024/07/02 02:42:21 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief strcpy boosted with SMO method
/// @param buffer dest e.g : char buffer[32];
/// @param src source e.g : "hi guys!"
/// @return 
char	*xstrcpy(char *buffer, const char *src)
{
	size_t	i;

	i = xstrlen(src);
	smo_copy(buffer, src, i + 1);
	buffer[i] = '\0';
	return (buffer);
}

/// @brief write function with error handler
/// @param fd file descriptor
/// @param data data content
/// @param n size of data content
void	xwrite(int fd, const void *data, size_t n)
{
	ssize_t	p;

	p = write(fd, data, n);
	if (p != (long)n)
		p = write(STDERR_FILENO, "write error\n", 12);
}
