/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:36:16 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/18 02:36:53 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_H
# define RT_RENDER_H

# define RT_PI 3.14159265
# define RT_SHININESS 32
# define INV_255 0.003921569
# include "rt_render/rt_render_types.h"
# include "rt_parser/rt_parser.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/ipc.h>
# include <X11/XKBlib.h>

# ifndef RT_PERTURB_STRENGHT
#  define RT_PERTURB_STRENGHT 20
# endif
# define RT_SC 0.1

/* frame pipeline */

void		rt_render_frame(t_RTContext *ctx, t_RTScene *scene)\
				__attribute__((__nonnull__(1, 2), __hot__));

t_RTRay		rt_camera_ray(size_t x, size_t y, t_RTScene *scene,\
				t_RTViewport *vp)\
				__attribute__((__nonnull__(3, 4), hot));

/* per-geometry cast/intersect/shade functions */
double		rt_sample(double u, double v, t_RTTexture *tx)\
				__attribute__((__nonnull__(3)));

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

void		rt_cast_cones(t_RTRay ray, t_RTScene *scene,
				t_RTHit *hit, double *closest) \
__attribute__((__nonnull__(2, 3, 4), hot));

void		rt_shade_lights(t_RTHit *hit, t_RTScene *scene, double *rgb)\
				__attribute__((__nonnull__(1, 2, 3)));

t_u32a		rt_shade(t_RTHit *hit, t_RTScene *scene)\
__attribute__((__nonnull__(1, 2)));

void		rt_render_line(t_RTContext *ctx, t_RTScene *scene, size_t y)\
				__attribute__((__nonnull__(1, 2), __hot__));

double		rt_intersect_cylinder(t_RTRay ray, size_t i,
				t_RTCylinderBuffer *buf)
			__attribute__((__nonnull__(3)));

double		rt_intersect_cyl_full(t_RTRay ray, size_t i,
				t_RTCylinderBuffer *buf, t_3dcoords *n)
			__attribute__((__nonnull__(3, 4)));

void		rt_handle_cy_tx(t_RTHit *hit, t_RTCylinderBuffer buf, size_t i)\
				__attribute__((__nonnull__(1)));

t_u32a		rt_sample_color(double u, double v, t_RTColortx *cx)\
				__attribute__((__nonnull__(3)));

double		rt_intersect_cone(t_RTRay ray, size_t i,
				t_RTConeBuffer *buf, int *is_cap)\
				__attribute__((__nonnull__(3, 4), pure));

void		rt_handle_axis_limits(t_RTstate *state);

#endif
