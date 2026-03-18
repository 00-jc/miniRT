/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>        +#+  +:+      +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 01:10:32 by asoria            #+#    #+#             */
/*   Updated: 2026/03/18 13:20:29 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_render/rt_render.h"

#define CONE_EPS 1e-5

__attribute__((__always_inline__, __nonnull__(3), pure))
inline t_3dcoords	rt_cone_abc(t_RTRay ray, size_t i,
		t_RTConeBuffer *buf)
{
	t_3dcoords	oc;
	double		doc;
	double		occ;

	oc = ft_3dsub(ray.origin, buf->apex[i]);
	doc = ft_3ddot(ray.dir, buf->axis[i]);
	occ = ft_3ddot(oc, buf->axis[i]);
	return ((t_3dcoords){doc * doc - buf->m[i],
		2.0 * (doc * occ - buf->m[i] * ft_3ddot(ray.dir, oc)),
		occ * occ - buf->m[i] * ft_3ddot(oc, oc), 0});
}

__attribute__((__always_inline__, __nonnull__(3), pure))
inline double	rt_check_cone_height(t_RTRay ray, size_t i,
		t_RTConeBuffer *buf, double t)
{
	t_3dcoords	point;
	t_3dcoords	oc;
	double		proj;

	if (t <= CONE_EPS)
		return (-1.0);
	point = ft_3dadd(ray.origin,
			ft_3dmul(ray.dir, (t_3dcoords){t, t, t, 0}));
	oc = ft_3dsub(point, buf->apex[i]);
	proj = ft_3ddot(oc, buf->axis[i]);
	if (proj <= CONE_EPS && proj >= -buf->wh[i].y - CONE_EPS)
		return (t);
	return (-1.0);
}

__attribute__((__always_inline__, __nonnull__(3), pure))
inline double	rt_check_cone_cap(t_RTRay ray, size_t i,
		t_RTConeBuffer *buf)
{
	t_3dcoords	oc;
	t_3dcoords	point;
	double		denom;
	double		t;
	double		radius;

	denom = ft_3ddot(ray.dir, buf->axis[i]);
	if (ft_fabs(denom) < CONE_EPS)
		return (-1.0);
	oc = ft_3dsub(buf->coords[i], ray.origin);
	t = ft_3ddot(oc, buf->axis[i]) / denom;
	if (t <= CONE_EPS)
		return (-1.0);
	point = ft_3dadd(ray.origin,
			ft_3dmul(ray.dir, (t_3dcoords){t, t, t, 0}));
	oc = ft_3dsub(point, buf->coords[i]);
	radius = buf->wh[i].x * 0.5;
	if (ft_3ddot(oc, oc) <= radius * radius + CONE_EPS)
		return (t);
	return (-1.0);
}

__attribute__((__always_inline__, __nonnull__(3), pure))
inline double	rt_cone_lateral_t(t_RTRay ray, size_t i,
		t_RTConeBuffer *buf, t_3dcoords abc)
{
	double	disc;
	double	t1;
	double	t2;

	disc = abc.y * abc.y - 4.0 * abc.x * abc.z;
	if (disc < 0.0)
		return (-1.0);
	disc = ft_dsqrt(disc);
	t1 = rt_check_cone_height(ray, i, buf,
			(-abc.y - disc) / (2.0 * abc.x));
	t2 = rt_check_cone_height(ray, i, buf,
			(-abc.y + disc) / (2.0 * abc.x));
	if (t1 > CONE_EPS && t2 > CONE_EPS)
		return ((t1 < t2) * t1 + (t2 <= t1) * t2);
	if (t1 > CONE_EPS)
		return (t1);
	return (t2);
}

__attribute__((__always_inline__, __nonnull__(3, 4), pure))
inline double	rt_intersect_cone(t_RTRay ray, size_t i,
		t_RTConeBuffer *buf, int *is_cap)
{
	t_3dcoords	abc;
	double		t;
	double		t_cap;

	*is_cap = 0;
	abc = rt_cone_abc(ray, i, buf);
	if (ft_fabs(abc.x) < CONE_EPS)
		return (-1.0);
	t = rt_cone_lateral_t(ray, i, buf, abc);
	t_cap = rt_check_cone_cap(ray, i, buf);
	if (t_cap > CONE_EPS && (t <= CONE_EPS || t_cap < t))
		return ((void)(*is_cap = 1), t_cap);
	return (t);
}
