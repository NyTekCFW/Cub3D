/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_simd_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:38:54 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/29 02:13:26 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

static void	_smo_set(void *dst, const void *v, size_t n, size_t *i)
{
	__uint16_t	s;
	__uint8_t	c;

	s = *(__uint16_t *)v;
	c = *(__uint8_t *)v;
	if ((*i + __SIZEOF_SHORT__) < n)
	{
		*(__uint16_t *)(dst + *i) = s;
		*i += __SIZEOF_SHORT__;
	}
	else if ((*i + 1) < n)
	{
		*(__uint8_t *)(dst + *i) = c;
		*i += 1;
	}
	else
		*i += 1;
}

void	smo_set(void *dst, __uint8_t c, size_t n)
{
	size_t		i;
	__uint64_t	p;

	i = 0;
	p = ((__uint64_t)c & 0xFF) * 0x0101010101010101ULL;
	while (i < n)
	{
		if ((i + __SIZEOF_LONG__) < n)
		{
			*(__uint64_t *)(dst + i) = p;
			i += __SIZEOF_LONG__;
		}
		else if ((i + __SIZEOF_INT__) < n)
		{
			*(__uint32_t *)(dst + i) = p & 0xFFFFFFFF;
			i += __SIZEOF_INT__;
		}
		else
			_smo_set(dst, &p, n, &i);
	}
}
