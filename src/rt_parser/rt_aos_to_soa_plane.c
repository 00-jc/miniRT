/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_aos_to_soa_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 02:41:48 by asoria            #+#    #+#             */
/*   Updated: 2026/03/09 03:48:18 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"

__attribute__((__always_inline__))
inline t_taggedresult	rt_alloc_soa_plane(t_RTPlaneBuffer *buf,
		size_t n, t_arena *arena)
{
	buf->size = n;
	buf->coords = ft_arena_alloc(arena, n * sizeof(t_3dcoords), 32);
	buf->axis = ft_arena_alloc(arena, n * sizeof(t_3dcoords), 32);
	buf->color = ft_arena_alloc(arena, n * sizeof(t_u32a), 4);
	if (!buf->coords || !buf->axis || !buf->color)
		return (KO);
	return (OK);
}

__attribute__((__always_inline__))
inline void	rt_populate_soa_plane(t_RTPlaneBuffer *buf,
		t_vec *aos)
{
	size_t		i;
	t_RTPlane	*p;

	i = 0;
	while (i < buf->size)
	{
		p = (t_RTPlane *)ft_vec_get(aos, i, sizeof(t_RTPlane));
		buf->coords[i] = p->coords;
		buf->axis[i] = p->axis;
		buf->color[i] = p->color;
		i++;
	}
}

__attribute__((__always_inline__))
inline t_taggedresult	rt_aos_to_soa_plane(t_RTPlaneBuffer *buf,
		t_vec *aos, t_arena *arena)
{
	size_t	n;

	n = ft_vec_len(aos, sizeof(t_RTPlane));
	if (rt_alloc_soa_plane(buf, n, arena) == KO)
		return (KO);
	rt_populate_soa_plane(buf, aos);
	return (OK);
}
