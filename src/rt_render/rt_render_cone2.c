/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_cone2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>        +#+  +:+      +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 01:03:57 by asoria            #+#    #+#             */
/*   Updated: 2026/04/05 19:28:03 by asoria           ###   ########.fr       */
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

__attribute__((__always_inline__, __nonnull__(1, 2, 3)))
inline void	rt__handle_hit_cone(t_RTHit *hit, t_RTRay *ray,
	t_RTConeBuffer *buffer, size_t best[2])
{
	hit->point = ft_3dadd(ray->origin,
			ft_3dmul(ray->dir, (t_3dcoords){hit->t, hit->t, hit->t, 0}));
	hit->color = buffer->color[best[0]];
	hit->cx = buffer->cx[best[0]];
	if (best[1])
		hit->normal = ft_3dmul(buffer->axis[best[0]],
				(t_3dcoords){-1, -1, -1, 0});
	else
		hit->normal = rt_cone_normal(hit->point,
				best[0], buffer);
	rt_handle_cone_tx(hit, buffer, best[0], (int)best[1]);
}

__attribute__((__nonnull__(2, 3, 4), hot))
void	rt_cast_cones(t_RTRay ray, t_RTScene *scene,
		t_RTHit *hit, double *closest)
{
	double		t;
	size_t		i;
	int			is_cap;
	size_t		best;
	t_u8		should_com;

	i = 0;
	is_cap = 0;
	should_com = 0;
	best = 0;
	while (i < scene->rt_cone_buffer.size)
	{
		t = rt_intersect_cone(ray, i, &scene->rt_cone_buffer, &is_cap);
		if (t > CONE_EPS && t < *closest)
		{
			*closest = t;
			hit->t = t;
			should_com = 1;
			best = i;
		}
		i++;
	}
	if (should_com)
		rt__handle_hit_cone(hit, &ray, &scene->rt_cone_buffer,
			(size_t [2]){best, (size_t)is_cap});
}
