/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_frame.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 23:33:23 by asoria            #+#    #+#             */
/*   Updated: 2026/03/12 23:33:43 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"

/*
 * no shading yet, it can be injected by replacing hit.color by
 * rt_shading() in the future :)
*/
__attribute__((__always_inline__, __nonnull__(3, 4), hot))
static inline t_u32a	rt_cast_ray(size_t x, size_t y,
		t_RTContext *ctx, t_RTScene *scene)
{
	t_RTRay	ray;
	t_RTHit	hit;
	double	closest;

	ray = rt_camera_ray(x, y, ctx, scene);
	closest = 1e9;
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
	size_t	x;
	size_t	y;

	y = 0;
	while (y < ctx->display_height)
	{
		x = 0;
		while (x < ctx->display_width)
		{
			ctx->rt_img->data[y * ctx->display_width + x]
				= rt_cast_ray(x, y, ctx, scene);
			x++;
		}
		y++;
	}
}
