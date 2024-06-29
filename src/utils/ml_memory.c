/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:32:34 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/28 23:37:53 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

//smo_copy(dest, src, n);
void	*xmemcpy(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	smo_copy(dest, src, n + 1);
	return (dest);
}

void	*xmemset(void *s, int c, size_t n)
{
	__uint8_t	ux;

	ux = (__uint8_t)c;
	smo_set(s, ux, n);
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
