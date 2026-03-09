/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_aos_to_soa_cylinder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 02:41:48 by asoria            #+#    #+#             */
/*   Updated: 2026/03/09 16:18:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"

__attribute__((__always_inline__, __nonnull__(1, 3)))
inline t_taggedresult	rt_alloc_soa_cylinder(t_RTCylinderBuffer *buf,
		size_t n, t_arena *arena)
{
	buf->size = n;
	buf->coords = ft_arena_alloc(arena, n * sizeof(t_3dcoords), 32);
	buf->axis = ft_arena_alloc(arena, n * sizeof(t_3dcoords), 32);
	buf->wh = ft_arena_alloc(arena, n * sizeof(t_2packd), 16);
	buf->color = ft_arena_alloc(arena, n * sizeof(t_u32a), 4);
	if (!buf->coords || !buf->axis || !buf->wh || !buf->color)
		return (KO);
	return (OK);
}

__attribute__((__always_inline__, __nonnull__(1, 2)))
inline void	rt_populate_soa_cylinder(t_RTCylinderBuffer *buf,
		t_vec *aos)
{
	t_RTCylinder	*s;
	size_t			i;

	i = 0;
	while (i < buf->size)
	{
		s = (t_RTCylinder *)ft_vec_get(aos, i, sizeof(t_RTCylinder));
		buf->coords[i] = s->coords;
		buf->axis[i] = s->axis;
		buf->wh[i] = s->wh;
		buf->color[i] = s->color;
		i++;
	}
}

__attribute__((__always_inline__, __nonnull__(1, 2, 3)))
inline t_taggedresult	rt_aos_to_soa_cylinder(
		t_RTCylinderBuffer *buf, t_vec *aos, t_arena *arena)
{
	size_t	n;

	n = ft_vec_len(aos, sizeof(t_RTCylinder));
	if (rt_alloc_soa_cylinder(buf, n, arena) == KO)
		return (KO);
	rt_populate_soa_cylinder(buf, aos);
	return (OK);
}
