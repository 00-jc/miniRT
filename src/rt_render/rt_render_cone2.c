/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_cone2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>        +#+  +:+      +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 01:03:57 by asoria            #+#    #+#             */
/*   Updated: 2026/03/18 02:26:53 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_render/rt_render.h"

#define CONE_EPS 1e-5

__attribute__((__always_inline__))
inline t_3dcoords	rt_cone_normal(t_3dcoords point, size_t i,
		t_RTConeBuffer *buf)
{
	t_3dcoords	apex;
	t_3dcoords	oc;
	double		proj;
	double		factor;

	apex = ft_3dadd(buf->coords[i], ft_3dmul(buf->axis[i],
				(t_3dcoords){buf->wh[i].y, buf->wh[i].y,
				buf->wh[i].y, 0}));
	oc = ft_3dsub(point, apex);
	proj = ft_3ddot(oc, buf->axis[i]);
	factor = (1.0 + (buf->wh[i].x * 0.5 / buf->wh[i].y)
			* (buf->wh[i].x * 0.5 / buf->wh[i].y)) * proj;
	return (ft_3dunit(ft_3dsub(oc, ft_3dmul(buf->axis[i],
					(t_3dcoords){factor, factor, factor, 0}))));
}

__attribute__((__nonnull__(2, 3, 4), hot))
void	rt_cast_cones(t_RTRay ray, t_RTScene *scene,
		t_RTHit *hit, double *closest)
{
	double	t;
	size_t	i;
	int		is_cap;

	i = 0;
	while (i < scene->rt_cone_buffer.size)
	{
		t = rt_intersect_cone(ray, i, &scene->rt_cone_buffer, &is_cap);
		if (t > CONE_EPS && t < *closest)
		{
			*closest = t;
			hit->t = t;
			hit->point = ft_3dadd(ray.origin,
					ft_3dmul(ray.dir, (t_3dcoords){t, t, t, 0}));
			hit->color = scene->rt_cone_buffer.color[i];
			if (is_cap)
				hit->normal = ft_3dmul(scene->rt_cone_buffer.axis[i],
						(t_3dcoords){-1, -1, -1, 0});
			else
				hit->normal = rt_cone_normal(hit->point,
						i, &scene->rt_cone_buffer);
		}
		i++;
	}
}
