/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:32:34 by lchiva            #+#    #+#             */
/*   Updated: 2024/05/31 13:57:32 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

void	*xmemcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	if (!dest && !src)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dest);
}

void	*xmemset(void *s, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	ux;

	dest = s;
	ux = (unsigned char)c;
	while (n--)
		*dest++ = ux;
	return (s);
}

void	*xcalloc(size_t nmemb, size_t size)
{
	void	*mc;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (((size * nmemb) / nmemb) != size)
		return (NULL);
	mc = malloc(nmemb * size);
	if (!mc)
		return (NULL);
	xmemset(mc, 0, nmemb * size);
	return (mc);
}

int	xalloc(void **var, size_t nmemb, size_t ts)
{
	if (nmemb == 0 || ts == 0)
		return (0);
	if (((ts * nmemb) / nmemb) != ts)
		return (0);
	*var = malloc(nmemb * ts);
	if (!*var)
		return (0);
	xmemset(*var, 0, nmemb * ts);
	return (1);
}

void	xfree(void **data)
{
	if (data && *data)
	{
		free(*data);
		*data = NULL;
	}
}
