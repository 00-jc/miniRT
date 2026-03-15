/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/15 02:05:07 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_render/rt_render.h"

extern double	pow(double x, double y);

/*
* rgb[0 - 2] diffuse light, will be mult by color
* rgb[3 - 5] specular light added directly no color
*/

__attribute__((__always_inline__))
static inline double	rt_specular(t_RTHit *hit, t_3dcoords ld,
	double brightness)
{
	t_3dcoords	reflect;
	double		dot_ln;
	double		spec_dot;

	dot_ln = 2.0 * ft_3ddot(ld, hit->normal);
	reflect = ft_3dsub(ft_3dmul(hit->normal,
				(t_3dcoords){dot_ln, dot_ln, dot_ln, 0}), ld);
	spec_dot = ft_3ddot(reflect, hit->view_dir);
	if (spec_dot < 0)
		spec_dot = 0;
	return (pow(spec_dot, RT_SHININESS) * brightness);
}

// weird constant is inverse of 255 all bit stuff are biutmasks
// per channels
__attribute__((__always_inline__))
static void	rt_shade_light(t_RTHit *hit, t_RTLightBuffer *buf,
	size_t i, double *rgb)
{
	t_3dcoords	ld;
	double		diff;
	double		spec;

	ld = ft_3dunit(ft_3dsub(buf->coords[i], hit->point));
	diff = ft_3ddot(hit->normal, ld) * buf->brightness[i];
	if (diff < 0)
		diff = 0;
	spec = rt_specular(hit, ld, buf->brightness[i]);
	rgb[0] += ((buf->color[i] >> 16) & 0xFF) * INV_255 * diff;
	rgb[1] += ((buf->color[i] >> 8) & 0xFF) * INV_255 * diff;
	rgb[2] += (buf->color[i] & 0xFF) * INV_255 * diff;
	rgb[3] += ((buf->color[i] >> 16) & 0xFF) * INV_255 * spec;
	rgb[4] += ((buf->color[i] >> 8) & 0xFF) * INV_255 * spec;
	rgb[5] += (buf->color[i] & 0xFF) * INV_255 * spec;
}

void	rt_shade_lights(t_RTHit *hit, t_RTScene *scene, double *rgb)
{
	size_t	i;

	i = 0;
	while (i < scene->rt_light_buffer.size)
	{
		rt_shade_light(hit, &scene->rt_light_buffer, i, rgb);
		i++;
	}
}
