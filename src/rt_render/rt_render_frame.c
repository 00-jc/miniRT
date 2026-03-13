/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_frame.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 23:33:23 by asoria            #+#    #+#             */
/*   Updated: 2026/03/13 16:19:11 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_render/rt_render.h"

/*
 * no shading yet, it can be injected by replacing hit.color by
 * rt_shading() in the future :)
*/
__attribute__((__always_inline__, __nonnull__(3, 4), hot))
static inline t_u32a	rt_cast_ray(size_t x, size_t y, t_RTScene *scene,
		t_RTViewport *vp)
{
	t_RTRay	ray;
	t_RTHit	hit;
	double	closest;

	ray = rt_camera_ray(x, y, scene, vp);
	closest = (t_dp){.i = 0x7FF0000000000000}.f;
	hit.t = -1;
	rt_cast_spheres(ray, scene, &hit, &closest);
	rt_cast_planes(ray, scene, &hit, &closest);
	rt_cast_cylinders(ray, scene, &hit, &closest);
	if (hit.t < 0)
		return (0x000000);
	return (hit.color);
}

__attribute__((__nonnull__(1, 2), __hot__))
void	rt_render_frame(t_RTContext *ctx, t_RTScene *scene)
{
	t_u32a		*px;
	t_u32a		*end;
	size_t		x;
	size_t		y;

	ctx->vp.right = ft_3dunit(ft_3dcross(scene->rt_camera.axis,
				(t_3dcoords){0, 1, 0, 0}));
	ctx->vp.up = ft_3dunit(ft_3dcross(ctx->vp.right, scene->rt_camera.axis));
	ctx->vp.forward = scene->rt_camera.axis;
	px = ctx->rt_img->data;
	end = px + ctx->pix_num;
	x = 0;
	y = 0;
	while (px < end)
	{
		*px++ = rt_cast_ray(x++, y, scene, &ctx->vp);
		y = (((x == ctx->display_width) * (y + 1))
			| ((x != ctx->display_width) * y));
		x = (((size_t)(x == ctx->display_width) * 0)
			| ((x != ctx->display_width) * x));
	}
}
