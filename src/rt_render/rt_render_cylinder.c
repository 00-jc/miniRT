/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 23:28:59 by asoria            #+#    #+#             */
/*   Updated: 2026/03/16 21:07:29 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_render/rt_render.h"

__attribute__((__always_inline__, pure))
inline t_3dcoords	rt_cylinder_abc(t_RTRay ray, size_t i,
		t_RTCylinderBuffer *buf)
{
	t_3dcoords	oc;
	t_3dcoords	d_perp;
	t_3dcoords	oc_perp;
	double		radius;
	double		tmp;

	radius = buf->wh[i].x * 0.5;
	oc = ft_3dsub(ray.origin, buf->coords[i]);
	tmp = ft_3ddot(ray.dir, buf->axis[i]);
	d_perp = ft_3dsub(ray.dir,
			ft_3dmul(buf->axis[i], (t_3dcoords){tmp, tmp, tmp, 0}));
	tmp = ft_3ddot(oc, buf->axis[i]);
	oc_perp = ft_3dsub(oc,
			ft_3dmul(buf->axis[i], (t_3dcoords){tmp, tmp, tmp, 0}));
	return ((t_3dcoords){ft_3ddot(d_perp, d_perp),
		2.0 * ft_3ddot(d_perp, oc_perp),
		ft_3ddot(oc_perp, oc_perp) - radius * radius, 0});
}

__attribute__((__always_inline__))
inline double	rt_check_cap_t(t_RTRay ray, size_t i,
		t_RTCylinderBuffer *buf, double t)
{
	t_3dcoords	point;
	t_3dcoords	oc;
	double		proj;
	double		half_h;

	half_h = buf->wh[i].y * 0.5;
	point = ft_3dadd(ray.origin,
			ft_3dmul(ray.dir, (t_3dcoords){t, t, t, 0}));
	oc = ft_3dsub(point, buf->coords[i]);
	proj = ft_3ddot(oc, buf->axis[i]);
	if (proj >= -half_h && proj <= half_h)
		return (t);
	return (-1.0);
}

__attribute__((__always_inline__))
inline double	rt_intersect_cylinder(t_RTRay ray, size_t i,
		t_RTCylinderBuffer *buf)
{
	t_3dcoords	abc;
	double		disc;
	double		t;

	abc = rt_cylinder_abc(ray, i, buf);
	if (abc.x < 1e-6)
		return (-1.0);
	disc = abc.y * abc.y - 4.0 * abc.x * abc.z;
	if (disc < 0)
		return (-1.0);
	disc = ft_dsqrt(disc);
	t = rt_check_cap_t(ray, i, buf,
			(-abc.y - disc) / (2.0 * abc.x));
	return (((t > 0) * t) + ((t < 0) * rt_check_cap_t(ray, i, buf,
				(-abc.y + disc) / (2.0 * abc.x))));
}

__attribute__((__always_inline__, __nonnull__(2, 3, 4), hot))
inline void	rt_cast_cylinders(t_RTRay ray, t_RTScene *scene,
		t_RTHit *hit, double *closest)
{
	size_t		i;
	double		t;
	t_3dcoords	normal;

	i = 0;
	while (i < scene->rt_cylinder_buffer.size)
	{
		t = rt_intersect_cyl_full(ray, i,
				&scene->rt_cylinder_buffer, &normal);
		if (t > 0 && t < *closest)
		{
			*closest = t;
			hit->t = t;
			hit->color = scene->rt_cylinder_buffer.color[i];
			hit->point = ft_3dadd(ray.origin,
					ft_3dmul(ray.dir, (t_3dcoords){t, t, t, 0}));
			hit->normal = normal;
		}
		i++;
	}
}
