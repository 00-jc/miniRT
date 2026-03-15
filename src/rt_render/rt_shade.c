/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shade.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:41:48 by asoria            #+#    #+#             */
/*   Updated: 2026/03/15 06:18:10 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_render/rt_render.h"

__attribute__((__always_inline__))
inline void	rt_shade_ambient(t_RTAmbientLight *amb, double *rgb)
{
	double	modb;

	modb = INV_255 * amb->brightness;
	rgb[0] += ((amb->color >> 16) & 0xFF) * modb;
	rgb[1] += ((amb->color >> 8) & 0xFF) * modb;
	rgb[2] += (amb->color & 0xFF) * modb;
}

__attribute__((__always_inline__))
inline t_u32a	rt_pack_color(double r, double g, double b)
{
	return (((t_u32a)(r * 255) << 16)
		| ((t_u32a)(g * 255) << 8) | (t_u32a)(b * 255));
}

__attribute__((const, hot, __always_inline__))
inline double	rt__fmin1(double f)
{
	t_dp	val;
	t_dp	one;
	t_u64	mask;

	val.f = f;
	one.f = 1.0;
	mask = -((t_u64)(val.i > one.i));
	val.i = (mask & one.i) | (~mask & val.i);
	return (val.f);
}

// non specular

__attribute__((__always_inline__, __nonnull__(1, 2)))
inline t_u32a	rt_shade(t_RTHit *hit, t_RTScene *scene)
{
	double	rgb[6];
	double	sr;
	double	sg;
	double	sb;

	*(t_4packd * restrict const)rgb = (t_4packd){0, 0, 0, 0};
	*(t_2packd * restrict const)(rgb + 4) = (t_2packd){0, 0};
	rt_shade_ambient(&scene->rt_ambient, rgb);
	rt_shade_lights(hit, scene, rgb);
	sr = ((hit->color >> 16) & 0xFF) * INV_255 * rgb[0] + rgb[3];
	sg = ((hit->color >> 8) & 0xFF) * INV_255 * rgb[1] + rgb[4];
	sb = (hit->color & 0xFF) * INV_255 * rgb[2] + rgb[5];
	sr = rt__fmin1(sr);
	sg = rt__fmin1(sg);
	sb = rt__fmin1(sb);
	return (rt_pack_color(sr, sg, sb));
}
