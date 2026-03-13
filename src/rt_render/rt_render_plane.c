/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/13 03:55:08 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"

/*
** ray-plane intersection:
**   t = dot(plane_point - ray_origin, normal) / dot(ray_dir, normal)
** Returns -1 when the ray is parallel to the plane or hits from behind.
*/
__attribute__((__always_inline__))
inline double	rt_intersect_plane(t_RTRay ray, size_t i,
		t_RTPlaneBuffer *buf)
{
	t_3dcoords	oc;
	double		denom;
	double		t;

	denom = ft_3ddot(ray.dir, buf->axis[i]);
	if (denom > -1e-6 && denom < 1e-6)
		return (-1.0);
	oc = ft_3dsub(buf->coords[i], ray.origin);
	t = ft_3ddot(oc, buf->axis[i]) / denom;
	if (t < 0)
		return (-1.0);
	if (t > 1e3)
		return (-1.0);
	return (t);
}

__attribute__((__always_inline__, __nonnull__(2, 3, 4), hot))
inline void	rt_cast_planes(t_RTRay ray, t_RTScene *scene,
		t_RTHit *hit, double *closest)
{
	double	t;
	size_t	i;

	i = 0;
	while (i < scene->rt_plane_buffer.size)
	{
		t = rt_intersect_plane(ray, i, &scene->rt_plane_buffer);
		if (t > 0 && t < *closest)
		{
			*closest = t;
			hit->t = t;
			hit->color = scene->rt_plane_buffer.color[i];
			hit->point = ft_3dadd(ray.origin,
					ft_3dmul(ray.dir, (t_3dcoords){t, t, t, 0}));
			hit->normal = scene->rt_plane_buffer.axis[1];
		}
		i++;
	}
}
