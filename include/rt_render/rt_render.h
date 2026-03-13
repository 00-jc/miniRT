/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:36:16 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/13 17:25:16 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_H
# define RT_RENDER_H

# define RT_PI 3.14159265
# include "rt_render/rt_render_types.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/ipc.h>
# include <X11/XKBlib.h>

/* frame pipeline */

void		rt_render_frame(t_RTContext *ctx, t_RTScene *scene)\
				__attribute__((__nonnull__(1, 2), __hot__));

t_RTRay		rt_camera_ray(size_t x, size_t y, t_RTScene *scene,\
				t_RTViewport *vp)\
				__attribute__((__nonnull__(3, 4), hot));

/* per-geometry cast functions */

void		rt_cast_spheres(t_RTRay ray, t_RTScene *scene,
				t_RTHit *hit, double *closest) \
__attribute__((__nonnull__(2, 3, 4), hot));

void		rt_cast_planes(t_RTRay ray, t_RTScene *scene,
				t_RTHit *hit, double *closest) \
__attribute__((__nonnull__(2, 3, 4), hot));

void		rt_cast_cylinders(t_RTRay ray, t_RTScene *scene,
				t_RTHit *hit, double *closest) \
__attribute__((__nonnull__(2, 3, 4), hot));

#endif
