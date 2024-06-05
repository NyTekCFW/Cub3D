/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_string_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:28:58 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/03 17:54:56 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/openmlx.h"

__uint32_t	xhashstr(const char *str)
{
	__uint32_t	hash;

	hash = 2784;
	while (*str++)
		hash = ((hash << 5) + hash) + (int)*str;
	return (hash);
}

__uint32_t	fnv1a_hash(const char *str)
{
	__uint32_t	hash;

	hash = 2166136261u;
	while (*str)
	{
		hash ^= (unsigned char)*str++;
		hash *= 16777619u;
	}
	return (hash);
}

int	xstrcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1++ == *s2++)
		;
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

size_t	xstrlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*xstrrchr(const char *s, int c)
{
	char		uc;
	const char	*last_occurrence;

	uc = (char)c;
	last_occurrence = NULL;
	while (*s != '\0')
	{
		if (*s == uc)
			last_occurrence = s;
		s++;
	}
	if (last_occurrence != NULL)
		return ((char *)last_occurrence);
	if (*s == uc)
		return ((char *)s);
	return (NULL);
}
