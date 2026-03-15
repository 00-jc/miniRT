/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_frame.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 23:33:23 by asoria            #+#    #+#             */
/*   Updated: 2026/03/14 22:41:52 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "rt_miniRT.h"
#include "rt_render/rt_render.h"

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
	hit.view_dir = ft_3dmul(ray.dir, (t_3dcoords){-1.0, -1.0, -1.0, 0.0});
	return (rt_shade(&hit, scene));
}

__attribute__((__nonnull__(1, 2, 3, 4), __hot__, __always_inline__))
static inline void	rt_inner(t_RTContext *ctx, t_RTScene *scene,
	size_t *xy[2], t_u32a *px)
{
	size_t	x;
	size_t	y;

	x = *xy[0];
	y = *xy[1];
	*px = rt_cast_ray(x++, y, scene, &ctx->vp);
	*xy[1] = (((x == ctx->display_width) * (y + 1))
			| ((x != ctx->display_width) * y));
	*xy[0] = (((size_t)(x == ctx->display_width) * 0)
			| ((x != ctx->display_width) * x));
}

__attribute__((__nonnull__(1, 2, 3, 4), __hot__, __always_inline__))
static inline void	rt_inner8(t_RTContext *ctx, t_RTScene *scene,
	size_t *xy[2], t_u32a *px)
{
	rt_inner(ctx, scene, xy, px++);
	rt_inner(ctx, scene, xy, px++);
	rt_inner(ctx, scene, xy, px++);
	rt_inner(ctx, scene, xy, px++);
	rt_inner(ctx, scene, xy, px++);
	rt_inner(ctx, scene, xy, px++);
	rt_inner(ctx, scene, xy, px++);
	rt_inner(ctx, scene, xy, px++);
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
	while (px + 8 < end)
	{
		rt_inner8(ctx, scene, (size_t *[2]){&x, &y}, px);
		px += 8;
	}
	while (px < end)
		rt_inner(ctx, scene, (size_t *[2]){&x, &y}, px++);
}
