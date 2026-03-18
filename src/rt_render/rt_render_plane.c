/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/18 15:16:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include <stdbool.h>
#include "rt_render/rt_render.h"

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
	return (t);
}

__attribute__((__always_inline__, __nonnull__(1, 3)))
inline void	rt_handle_plane_tx(t_RTHit *hit, t_RTTexture *tx, double abs[3])
{
	double		u;
	double		v;

	if (tx)
	{
		if (abs[1] > abs[0] && abs[1] > abs[2])
		{
			u = hit->point.x * RT_SC - __builtin_floor(hit->point.x * RT_SC);
			v = hit->point.z * RT_SC - __builtin_floor(hit->point.z * RT_SC);
		}
		else if (abs[0] > abs[2])
		{
			u = hit->point.y * RT_SC - __builtin_floor(hit->point.y * RT_SC);
			v = hit->point.z * RT_SC - __builtin_floor(hit->point.z * RT_SC);
		}
		else
		{
			u = hit->point.x * RT_SC - __builtin_floor(hit->point.x * RT_SC);
			v = hit->point.y * RT_SC - __builtin_floor(hit->point.y * RT_SC);
		}
		hit->tx = tx;
		hit->uv[0] = u;
		hit->uv[1] = v;
	}
}

__attribute__((__always_inline__, __nonnull__(1, 2, 3)))
inline void	rt__handle_hit_pl(t_RTHit *hit, t_RTRay *ray,
	t_RTPlaneBuffer *buffer, size_t best)
{
	double		abs[3];

	hit->color = buffer->color[best];
	hit->point = ft_3dadd(ray->origin, ft_3dmul(ray->dir,
				(t_3dcoords){hit->t, hit->t, hit->t, 0}));
	hit->normal = buffer->axis[best];
	hit->cx = buffer->cx[best];
	abs[0] = ft_fabs(hit->normal.x);
	abs[1] = ft_fabs(hit->normal.y);
	abs[2] = ft_fabs(hit->normal.z);
	rt_handle_plane_tx(hit, buffer->tx[best], abs);
}

__attribute__((__always_inline__, __nonnull__(2, 3, 4), hot))
inline void	rt_cast_planes(t_RTRay ray, t_RTScene *scene,
		t_RTHit *hit, double *closest)
{
	double		t;
	size_t		i;
	size_t		best;
	t_u8		run_comp;

	i = 0;
	best = 0;
	run_comp = 0;
	while (i < scene->rt_plane_buffer.size)
	{
		t = rt_intersect_plane(ray, i, &scene->rt_plane_buffer);
		if (t > 0 && t < *closest)
		{
			*closest = t;
			hit->t = t;
			best = i;
			run_comp = 1;
		}
		i++;
	}
	if (run_comp)
		rt__handle_hit_pl(hit, &ray, &scene->rt_plane_buffer, best);
}
