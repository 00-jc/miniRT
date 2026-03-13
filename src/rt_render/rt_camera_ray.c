/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 03:07:47 by asoria            #+#    #+#             */
/*   Updated: 2026/03/13 03:42:12 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"

/*
* builds a normalised ray direction given pre-computed viewport offsets nx/ny
* right = normalise(forward × world_up)
* up    = normalise(right × forward)
* dir   = normalise(forward + nx·right + ny·up)
*
* scale and aspect come precomputed via t_RTViewport
*/

__attribute__((__nonnull__(3), hot))
t_RTRay	rt_camera_ray(size_t x, size_t y, t_RTScene *scene, t_RTViewport vp)
{
	t_3dcoords	dir;
	double		nx;
	double		ny;

	nx = (2.0 * ((double)x + 0.5) * (double)vp.inv_width - 1.0)
		* vp.aspect * vp.scale;
	ny = (1.0 - 2.0 * ((double)y + 0.5) * (double)vp.inv_height)
		* vp.scale;
	dir = ft_3dunit(ft_3dadd(vp.forward,
				ft_3dadd(ft_3dmul(vp.right, (t_3dcoords){nx, nx, nx, 0}),
					ft_3dmul(vp.up, (t_3dcoords){ny, ny, ny, 0}))));
	return ((t_RTRay){.origin = scene->rt_camera.coords, .dir = dir});
}
