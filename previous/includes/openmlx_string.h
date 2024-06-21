/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_string.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 06:34:12 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/03 18:03:09 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_STRING_H
# define OPENMLX_STRING_H

__uint32_t	xhashstr(const char *str);
__uint32_t	fnv1a_hash(const char *str);
int			xstrcmp(const char *s1, const char *s2);
size_t		xstrlen(const char *str);
char		*xstrrchr(const char *s, int c);
char		*xstrcpy(char *buffer, const char *src);
#endif