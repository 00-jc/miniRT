/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shade.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:41:48 by asoria            #+#    #+#             */
/*   Updated: 2026/03/15 03:45:49 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_render/rt_render.h"

__attribute__((__always_inline__))
inline void	rt_shade_ambient(t_RTAmbientLight *amb, double *rgb)
{
	rgb[0] += ((amb->color >> 16) & 0xFF) * INV_255 * amb->brightness;
	rgb[1] += ((amb->color >> 8) & 0xFF) * INV_255 * amb->brightness;
	rgb[2] += (amb->color & 0xFF) * INV_255 * amb->brightness;
}

__attribute__((__always_inline__))
inline t_u32a	rt_pack_color(double r, double g, double b)
{
	return (((t_u32a)(r * 255) << 16)
		| ((t_u32a)(g * 255) << 8) | (t_u32a)(b * 255));
}

// non specular

__attribute__((__always_inline__, __nonnull__(1, 2)))
inline t_u32a	rt_shade(t_RTHit *hit, t_RTScene *scene)
{
	double	rgb[6];
	double	sr;
	double	sg;
	double	sb;

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	rgb[3] = 0;
	rgb[4] = 0;
	rgb[5] = 0;
	rt_shade_ambient(&scene->rt_ambient, rgb);
	rt_shade_lights(hit, scene, rgb);
	sr = ((hit->color >> 16) & 0xFF) * INV_255 * rgb[0] + rgb[3];
	sg = ((hit->color >> 8) & 0xFF) * INV_255 * rgb[1] + rgb[4];
	sb = (hit->color & 0xFF) * INV_255 * rgb[2] + rgb[5];
	if (sr > 1.0)
		sr = 1.0;
	if (sg > 1.0)
		sg = 1.0;
	if (sb > 1.0)
		sb = 1.0;
	return (rt_pack_color(sr, sg, sb));
}
