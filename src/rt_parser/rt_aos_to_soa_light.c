/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_aos_to_soa_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 02:41:48 by asoria            #+#    #+#             */
/*   Updated: 2026/03/09 03:58:45 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"

__attribute__((__always_inline__))
inline t_taggedresult	rt_alloc_soa_light(t_RTLightBuffer *buf,
		size_t n, t_arena *arena)
{
	buf->size = n;
	buf->coords = ft_arena_alloc(arena, n * sizeof(t_3dcoords), 32);
	buf->brightness = ft_arena_alloc(arena, n * sizeof(double), 8);
	buf->color = ft_arena_alloc(arena, n * sizeof(t_u32a), 4);
	if (!buf->coords || !buf->brightness || !buf->color)
		return (KO);
	return (OK);
}

__attribute__((__always_inline__))
inline void	rt_populate_soa_light(t_RTLightBuffer *buf,
		t_vec *aos)
{
	size_t		i;
	t_RTLight	*l;

	i = 0;
	while (i < buf->size)
	{
		l = (t_RTLight *)ft_vec_get(aos, i, sizeof(t_RTLight));
		buf->coords[i] = l->coords;
		buf->brightness[i] = l->brightness;
		buf->color[i] = l->color;
		i++;
	}
}

__attribute__((__always_inline__))
inline t_taggedresult	rt_aos_to_soa_light(t_RTLightBuffer *buf,
		t_vec *aos, t_arena *arena)
{
	size_t	n;

	n = ft_vec_len(aos, sizeof(t_RTLight));
	if (rt_alloc_soa_light(buf, n, arena) == KO)
		return (KO);
	rt_populate_soa_light(buf, aos);
	return (OK);
}
