/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 03:07:47 by asoria            #+#    #+#             */
/*   Updated: 2026/03/13 03:18:40 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"

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

/*
 *	precomputed scale and aspect so we dont have 91.200 operations per frame lmao
 */
__attribute__((__nonnull__(3), hot))
t_RTRay	rt_camera_ray(size_t x, size_t y, t_RTScene *scene, t_RTViewport vp)
{
	double	nx;
	double	ny;

	nx = (2.0 * ((double)x + 0.5) / (double)vp.width - 1.0)
		* vp.aspect * vp.scale;
	ny = (1.0 - 2.0 * ((double)y + 0.5) / (double)vp.height)
		* vp.scale;
	return ((t_RTRay){.origin = scene->rt_camera.coords,
		.dir = rt_build_ray_dir(scene, nx, ny)});
}
