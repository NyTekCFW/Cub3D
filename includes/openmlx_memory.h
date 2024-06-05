/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openmlx_memory.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 06:36:49 by lchiva            #+#    #+#             */
/*   Updated: 2024/04/04 06:38:12 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENMLX_MEMORY_H
# define OPENMLX_MEMORY_H

void	*xmemcpy(void *dest, const void *src, size_t n);
void	*xmemset(void *s, int c, size_t n);
void	*xcalloc(size_t nmemb, size_t size);
int		xalloc(void **var, size_t nmemb, size_t ts);
void	xfree(void **data);
#endif