/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/15 07:07:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include <stdbool.h>
#include "rt_render/rt_render.h"

#define R_B 0
#define R_C 1
#define R_D 2
#define R_R 3

__attribute__((__always_inline__))
inline double	rt_intersect_sphere(t_RTRay ray, size_t i,
		t_RTSphereBuffer *buf)
{
	t_3dcoords	oc;
	double		v[4];
	double		near;
	double		far;

	v[R_R] = buf->diameter[i] * 0.5;
	oc = ft_3dsub(ray.origin, buf->coords[i]);
	v[R_B] = 2.0 * ft_3ddot(oc, ray.dir);
	v[R_C] = ft_3ddot(oc, oc) - v[R_R] * v[R_R];
	v[R_D] = v[R_B] * v[R_B] - 4.0 * v[R_C];
	if (v[R_D] < 0)
		return (-1.0);
	v[R_D] *= ft_drsqrt(v[R_D]);
	near = (-v[R_B] - v[R_D]) * 0.5;
	far = (-v[R_B] + v[R_D]) * 0.5;
	if (near > 0)
		return (near);
	return (far);
}

__attribute__((__always_inline__))
inline t_3dcoords	rt_sphere_normal(t_3dcoords point, size_t i,
		t_RTSphereBuffer *buf)
{
	return (ft_3dunit(ft_3dsub(point, buf->coords[i])));
}

__attribute__((__always_inline__, __nonnull__(2, 3, 4), hot))
inline void	rt_cast_spheres(t_RTRay ray, t_RTScene *scene,
		t_RTHit *hit, double *closest)
{
	double	t;
	size_t	i;

	i = 0;
	while (i < scene->rt_sphere_buffer.size)
	{
		t = rt_intersect_sphere(ray, i, &scene->rt_sphere_buffer);
		if (t > 0 && t < *closest)
		{
			*closest = t;
			hit->t = t;
			hit->color = scene->rt_sphere_buffer.color[i];
			hit->point = ft_3dadd(ray.origin,
					ft_3dmul(ray.dir, (t_3dcoords){t, t, t, 0}));
			hit->normal = rt_sphere_normal(hit->point,
					i, &scene->rt_sphere_buffer);
		}
		i++;
	}
}
