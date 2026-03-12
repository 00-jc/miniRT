/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_frame.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:23:14 by asoria            #+#    #+#             */
/*   Updated: 2026/03/12 18:59:16 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"

static inline t_u32a	rt_cast_ray(size_t x, size_t y, t_RTContext *ctx, t_RTScene *scene)
{
	t_RTRay ray;
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
	return (rt_shade(hit, scene));
}

inline void	rt_render_frame(t_RTContext *ctx, t_RTScene *scene)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < ctx->display_height)
	{
		x = 0;
		while (x < ctx->display_width)
		{
			ctx->rt_img->data[y * ctx->display_width + x] =
				rt_cast_ray(x, y, ctx, scene);
			x++;
		}
		y++;
	}
}
