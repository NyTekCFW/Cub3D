/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_simd_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:47:49 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/29 02:13:30 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

/// @brief check if the 2 pixel in entry is valid
/// @param c 2 pixel
/// @return true if the 2 pixel are correct
static int	is_valid64_color(__uint64_t c)
{
	__uint32_t	upper;
	__uint32_t	lower;

	upper = (c >> 32) & 0xFFFFFFFF;
	lower = c & 0xFFFFFFFF;
	if (upper == 0 || upper == 0xFF000000)
		return (0);
	if (lower == 0 || lower == 0xFF000000)
		return (0);
	return (1);
}

/// @brief SIMD Memory Optimization for merge
/// @param dst memory destination
/// @param src memory source
/// @param n size to copy
void	smo_copy_img(void *dst, const void *src, size_t n)
{
	__uint32_t	c;
	__uint64_t	m;
	size_t		i;

	i = 0;
	while (i < n)
	{
		c = *(__uint32_t *)(src + i);
		m = *(__uint64_t *)(src + i);
		if ((i + __SIZEOF_LONG__) < n
			&& is_valid64_color(m))
		{
			*(__uint64_t *)(dst + i) = m;
			i += __SIZEOF_LONG__;
		}
		else if ((i + __SIZEOF_INT__) < n
			&& is_valid_color(c))
		{
			*(__uint32_t *)(dst + i) = c;
			i += __SIZEOF_INT__;
		}
		else
			i += __SIZEOF_INT__;
	}
}

static void	_smo_copy(void *dst, const void *src, size_t n, size_t *i)
{
	__uint16_t	s;
	__uint8_t	c;

	s = *(__uint16_t *)(src + *i);
	c = *(__uint8_t *)(src + *i);
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

/// @brief SIMD Memory Optimization
///for basic memory block copy
/// @param dst memory destination
/// @param src memory source
/// @param n size to copy
void	smo_copy(void *dst, const void *src, size_t n)
{
	__uint32_t	c;
	__uint64_t	m;
	size_t		i;

	i = 0;
	while (i < n)
	{
		c = *(__uint32_t *)(src + i);
		m = *(__uint64_t *)(src + i);
		if ((i + __SIZEOF_LONG__) < n)
		{
			*(__uint64_t *)(dst + i) = m;
			i += __SIZEOF_LONG__;
		}
		else if ((i + __SIZEOF_INT__) < n)
		{
			*(__uint32_t *)(dst + i) = c;
			i += __SIZEOF_INT__;
		}
		else
			_smo_copy(dst, src, n, &i);
	}
}
