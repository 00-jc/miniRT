/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_cylinder_caps.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:21:12 by asoria            #+#    #+#             */
/*   Updated: 2026/03/17 16:32:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_render/rt_render.h"
#include "rt_miniRT.h"

/*
*	ray-disk intersection for one end cap. + sign top cap, -sign bottomcap
*	returns t > 0 on hit, -1.0 on miss/parallel/behind. jaime optimizame esta
*/
__attribute__((__always_inline__, pure, __nonnull__(3)))
inline double	rt_intersect_cap(t_RTRay ray, size_t i,
		t_RTCylinderBuffer *buf, double sign)
{
	t_3dcoords	cap;
	t_3dcoords	oc;
	double		denom;
	double		t;
	double		r;

	r = buf->wh[i].x * 0.5;
	denom = ft_3ddot(ray.dir, buf->axis[i]);
	if (denom > -1e-6 && denom < 1e-6)
		return (-1.0);
	cap = ft_3dadd(buf->coords[i], ft_3dmul(buf->axis[i],
				(t_3dcoords){sign * buf->wh[i].y * 0.5,
				sign * buf->wh[i].y * 0.5,
				sign * buf->wh[i].y * 0.5, 0}));
	t = ft_3ddot(ft_3dsub(cap, ray.origin), buf->axis[i]) / denom;
	if (t < 0)
		return (-1.0);
	oc = ft_3dsub(ft_3dadd(ray.origin,
				ft_3dmul(ray.dir, (t_3dcoords){t, t, t, 0})), cap);
	if (ft_3ddot(oc, oc) > r * r)
		return (-1.0);
	return (t);
}

__attribute__((__always_inline__, pure, __nonnull__(3)))
inline t_3dcoords	rt_cylinder_normal(t_3dcoords point, size_t i,
		t_RTCylinderBuffer *buf)
{
	t_3dcoords	oc;
	double		proj;

	oc = ft_3dsub(point, buf->coords[i]);
	proj = ft_3ddot(oc, buf->axis[i]);
	oc = ft_3dsub(oc,
			ft_3dmul(buf->axis[i], (t_3dcoords){proj, proj, proj, 0}));
	return (ft_3dunit(oc));
}

/*
*	returns the closest positive t from choosing side, top cap and bottom cap,
*	writes the surface normal at that hit point into *n.
*	returns -1.0 when the ray misses the cylinder
*/
__attribute__((__always_inline__, pure, __nonnull__(3, 4)))
inline double	rt_intersect_cyl_full(t_RTRay ray, size_t i,
		t_RTCylinderBuffer *buf, t_3dcoords *n)
{
	double	ts;
	double	tt;
	double	tb;

	ts = rt_intersect_cylinder(ray, i, buf);
	tt = rt_intersect_cap(ray, i, buf, 1.0);
	tb = rt_intersect_cap(ray, i, buf, -1.0);
	if (tt > 0 && (ts <= 0 || tt < ts) && (tb <= 0 || tt <= tb))
		return ((void)(*n = buf->axis[i]), tt);
	if (tb > 0 && (ts <= 0 || tb < ts))
		return ((void)(*n = ft_3dmul(buf->axis[i], (t_3dcoords){-1, -1, -1, 0})),
				tb);
	if (ts > 0)
		return ((void)(*n = rt_cylinder_normal(ft_3dadd(ray.origin,
					ft_3dmul(ray.dir, (t_3dcoords){ts, ts, ts, 0})),
			i, buf)), ts);
	return (-1.0);
}
