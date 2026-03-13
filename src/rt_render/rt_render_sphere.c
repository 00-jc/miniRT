/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/13 17:32:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_render/rt_render.h"

__attribute__((__always_inline__))
inline double	rt_intersect_sphere(t_RTRay ray, size_t i,
		t_RTSphereBuffer *buf)
{
	t_3dcoords	oc;
	double		b;
	double		c;
	double		disc;
	double		radius;

	radius = buf->diameter[i] * 0.5;
	oc = ft_3dsub(ray.origin, buf->coords[i]);
	b = 2.0 * ft_3ddot(oc, ray.dir);
	c = ft_3ddot(oc, oc) - radius * radius;
	disc = b * b - 4.0 * c;
	if (disc < 0)
		return (-1.0);
	disc *= ft_drsqrt(disc);
	return ((((-b - disc) * 0.5 > 0) * ((-b - disc) * 0.5))
		+ ((-b - disc) * 0.5 <= 0) * ((-b + disc) * 0.5));
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
