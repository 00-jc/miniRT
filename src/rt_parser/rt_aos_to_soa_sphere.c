/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_aos_to_soa_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 02:41:48 by asoria            #+#    #+#             */
/*   Updated: 2026/03/16 22:05:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"

__attribute__((__always_inline__, __nonnull__(1, 3)))
inline t_taggedresult	rt_alloc_soa_sphere(t_RTSphereBuffer *buf,
		size_t n, t_arena *arena)
{
	buf->size = n;
	buf->coords = ft_arena_alloc(arena, n * sizeof(t_3dcoords), 32);
	buf->diameter = ft_arena_alloc(arena, n * sizeof(double), 8);
	buf->color = ft_arena_alloc(arena, n * sizeof(t_u32a), 4);
	buf->tx = (t_RTTexture **)ft_arena_alloc(arena,
			n * sizeof(t_RTTexture *), 8);
	if (!buf->coords || !buf->diameter || !buf->color)
		return (KO);
	return (OK);
}

__attribute__((__always_inline__, __nonnull__(1, 2)))
inline void	rt_populate_soa_sphere(t_RTSphereBuffer *buf,
		t_vec *aos)
{
	size_t		i;
	t_RTSphere	*s;

	i = 0;
	while (i < buf->size)
	{
		s = (t_RTSphere *)ft_vec_get(aos, i, sizeof(t_RTSphere));
		buf->coords[i] = s->coords;
		buf->diameter[i] = s->diameter;
		buf->color[i] = s->color;
		buf->tx[i] = s->tx;
		i++;
	}
}

__attribute__((__always_inline__, __nonnull__(1, 2, 3)))
inline t_taggedresult	rt_aos_to_soa_sphere(t_RTSphereBuffer *buf,
		t_vec *aos, t_arena *arena)
{
	size_t	n;

	n = ft_vec_len(aos, sizeof(t_RTSphere));
	if (rt_alloc_soa_sphere(buf, n, arena) == KO)
		return (KO);
	rt_populate_soa_sphere(buf, aos);
	return (OK);
}
