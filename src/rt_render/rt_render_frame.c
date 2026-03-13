/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_frame.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 23:33:23 by asoria            #+#    #+#             */
/*   Updated: 2026/03/13 03:56:26 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_render/rt_render.h"

extern double	tan(double x);

/*
 * no shading yet, it can be injected by replacing hit.color by
 * rt_shading() in the future :)
*/
__attribute__((__always_inline__, __nonnull__(3), hot))
static inline t_u32a	rt_cast_ray(size_t x, size_t y, t_RTScene *scene,
		t_RTViewport vp)
{
	t_RTRay	ray;
	t_RTHit	hit;
	double	closest;

	ray = rt_camera_ray(x, y, scene, vp);
	closest = 1e4;
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
	size_t			x;
	size_t			y;
	t_RTViewport	vp;

	vp.scale = tan((double)scene->rt_camera.fov * 0.5 * RT_PI / 180.0);
	vp.aspect = (double)ctx->display_width / (double)ctx->display_height;
	vp.width = ctx->display_width;
	vp.height = ctx->display_height;
	vp.inv_width = 1 / (double)ctx->display_width;
	vp.inv_height = 1 / (double)ctx->display_height;
	vp.right = ft_3dunit(ft_3dcross(scene->rt_camera.axis,
				(t_3dcoords){0, 1, 0, 0}));
	vp.up = ft_3dunit(ft_3dcross(vp.right, scene->rt_camera.axis));
	vp.forward = scene->rt_camera.axis;
	y = 0;
	while (y < ctx->display_height)
	{
		x = 0;
		while (x < ctx->display_width)
		{
			ctx->rt_img->data[y * ctx->display_width + x]
				= rt_cast_ray(x, y, scene, vp);
			x++;
		}
		y++;
	}
}
