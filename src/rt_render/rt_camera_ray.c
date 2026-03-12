/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/12 23:25:27 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define RT_PI	3.14159265358979323846
#include "rt_miniRT.h"

/*
** tan declared here meanwhile beautfiul and smart
** jaicastr develops one for the legenday libft
*/
extern double	tan(double x);

/*
** builds a normalised ray direction given pre-computed viewport offsets nx/ny
** right = normalise(forward × world_up)
** up    = normalise(right × forward)
** dir   = normalise(forward + nx·right + ny·up)
*/
__attribute__((__always_inline__))
static inline t_3dcoords	rt_build_ray_dir(t_RTScene *scene,
		double nx, double ny)
{
	t_3dcoords	right;
	t_3dcoords	up;
	t_3dcoords	dir;

	right = ft_3dunit(ft_3dcross(scene->rt_camera.axis,
				(t_3dcoords){0, 1, 0, 0}));
	up = ft_3dunit(ft_3dcross(right, scene->rt_camera.axis));
	dir = ft_3dadd(scene->rt_camera.axis,
			ft_3dadd(ft_3dmul(right, (t_3dcoords){nx, nx, nx, 0}),
				ft_3dmul(up, (t_3dcoords){ny, ny, ny, 0})));
	return (ft_3dunit(dir));
}

__attribute__((__nonnull__(3, 4), hot))
t_RTRay	rt_camera_ray(size_t x, size_t y,
		t_RTContext *ctx, t_RTScene *scene)
{
	double	scale;
	double	aspect;
	double	nx;
	double	ny;

	scale = tan((double)scene->rt_camera.fov * 0.5 * RT_PI / 180.0);
	aspect = (double)ctx->display_width / (double)ctx->display_height;
	nx = (2.0 * ((double)x + 0.5) / (double)ctx->display_width - 1.0)
		* aspect * scale;
	ny = (1.0 - 2.0 * ((double)y + 0.5) / (double)ctx->display_height)
		* scale;
	return ((t_RTRay){.origin = scene->rt_camera.coords,
		.dir = rt_build_ray_dir(scene, nx, ny)});
}
