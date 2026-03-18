/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_aos_to_soa_cone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 22:18:04 by asoria            #+#    #+#             */
/*   Updated: 2026/03/18 13:24:38 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"

__attribute__((__always_inline__, __nonnull__(1, 3)))
inline t_taggedresult	rt_alloc_soa_cone(t_RTConeBuffer *buf,
		size_t n, t_arena *arena)
{
	buf->size = n;
	buf->coords = ft_arena_alloc(arena, n * sizeof(t_3dcoords), 32);
	buf->apex = ft_arena_alloc(arena, n * sizeof(t_3dcoords), 32);
	buf->axis = ft_arena_alloc(arena, n * sizeof(t_3dcoords), 32);
	buf->wh = ft_arena_alloc(arena, n * sizeof(t_2packd), 16);
	buf->k = ft_arena_alloc(arena, n * sizeof(t_2packd), 8);
	buf->m = ft_arena_alloc(arena, n * sizeof(t_2packd), 8);
	buf->color = ft_arena_alloc(arena, n * sizeof(t_u32a), 4);
	if (!buf->coords || !buf->apex ||!buf->axis || !buf->wh
		|| !buf->color || !buf->k || !buf->m)
		return (KO);
	return (OK);
}

__attribute__((__always_inline__, __nonnull__(1, 2)))
inline void	rt_populate_soa_cone(t_RTConeBuffer *buf,
		t_vec *aos)
{
	t_RTCone	*s;
	size_t		i;

	i = 0;
	while (i < buf->size)
	{
		s = (t_RTCone *)ft_vec_get(aos, i, sizeof(t_RTCone));
		buf->coords[i] = s->coords;
		buf->apex[i] = ft_3dadd(s->coords, ft_3dmul(s->axis,
					(t_3dcoords){s->wh.y, s->wh.y, s->wh.y, 0}));
		buf->axis[i] = s->axis;
		buf->wh[i] = s->wh;
		buf->k[i] = (s->wh.x * 0.5) / s->wh.y;
		buf->m[i] = 1.0 / (1.0 + buf->k[i] * buf->k[i]);
		buf->color[i] = s->color;
		i++;
	}
}

__attribute__((__always_inline__, __nonnull__(1, 2, 3)))
inline t_taggedresult	rt_aos_to_soa_cone(t_RTConeBuffer *buf,
		t_vec *aos, t_arena *arena)
{
	size_t	n;

	n = ft_vec_len(aos, sizeof(t_RTCone));
	if (rt_alloc_soa_cone(buf, n, arena) == KO)
		return (KO);
	rt_populate_soa_cone(buf, aos);
	return (OK);
}
