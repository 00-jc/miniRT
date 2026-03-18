/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shade_lights.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/17 20:03:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_render/rt_render.h"
#include <stdbool.h>

__attribute__((__nonnull__(1), __always_inline__, hot))
inline void	rt_perturb_normal(t_RTHit *hit)
{
	const t_3dcoords	yax = (t_3dcoords){0, 1, 0, 0};
	const t_3dcoords	xax = (t_3dcoords){1, 0, 0, 0};
	t_3dcoords			tb[2];
	double				d[6];
	double				iwh[2];

	if (hit->tx)
	{
		iwh[0] = 1.0 / (double)hit->tx->width;
		iwh[1] = 1.0 / (double)hit->tx->height;
		d[0] = rt_sample(hit->uv[0] - iwh[0], hit->uv[1], hit->tx);
		d[1] = rt_sample(hit->uv[0] + iwh[0], hit->uv[1], hit->tx);
		d[2] = rt_sample(hit->uv[0], hit->uv[1] - iwh[1], hit->tx);
		d[3] = rt_sample(hit->uv[0], hit->uv[1] + iwh[1], hit->tx);
		d[4] = (d[1] - d[0]) * RT_PERTURB_STRENGHT;
		d[5] = (d[3] - d[2]) * RT_PERTURB_STRENGHT;
		if (ft_fabs(hit->normal.y) < 0.999)
			tb[0] = ft_3dunit(ft_3dcross(yax, hit->normal));
		else
			tb[0] = ft_3dunit(ft_3dcross(xax, hit->normal));
		tb[1] = ft_3dcross(hit->normal, tb[0]);
		hit->normal = ft_3dunit(ft_3dsub(hit->normal,
					ft_3dadd(ft_3dmul(tb[0], (t_3dcoords){d[4], d[4], d[4], 0}),
						ft_3dmul(tb[1], (t_3dcoords){d[5], d[5], d[5], 0}))));
	}
}

/*
* rgb[0 - 2] diffuse light, will be mult by color
* rgb[3 - 5] specular light added directly no color
*/
__attribute__((__always_inline__, __nonnull__(1), hot))
inline double	rt_specular(t_RTHit *hit, t_3dcoords ld,
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
	spec_dot *= spec_dot;
	spec_dot *= spec_dot;
	spec_dot *= spec_dot;
	spec_dot *= spec_dot;
	spec_dot *= spec_dot;
	return (spec_dot * brightness);
}

// weird constant is inverse of 255 all bit stuff are biutmasks
// per channels
__attribute__((__always_inline__, __nonnull__(1, 2), hot))
inline void	rt_shade_light(t_RTHit *hit, t_RTLightBuffer *buf,
	size_t i, double *rgb)
{
	t_3dcoords	ld;
	t_u32a		color;
	double		diff;
	double		spec;
	double		mulcache[2];

	color = buf->color[i];
	ld = ft_3dunit(ft_3dsub(buf->coords[i], hit->point));
	diff = ft_3ddot(hit->normal, ld) * buf->brightness[i];
	if (diff < 0)
		diff = 0;
	spec = rt_specular(hit, ld, buf->brightness[i]);
	mulcache[0] = INV_255 * diff;
	mulcache[1] = INV_255 * spec;
	rgb[0] += ((color >> 16) & 0xFF) * mulcache[0];
	rgb[1] += ((color >> 8) & 0xFF) * mulcache[0];
	rgb[2] += (color & 0xFF) * mulcache[0];
	rgb[3] += ((color >> 16) & 0xFF) * mulcache[1];
	rgb[4] += ((color >> 8) & 0xFF) * mulcache[1];
	rgb[5] += (color & 0xFF) * mulcache[1];
}

__attribute__((__nonnull__(1, 2, 3), hot, __always_inline__))
inline void	rt_shade_lights(t_RTHit *hit, t_RTScene *scene, double *rgb)
{
	size_t	i;

	i = 0;
	rt_perturb_normal(hit);
	if (hit->cx)
		hit->color = rt_sample_color(hit->uv[0], hit->uv[1], hit->cx);
	while (i < scene->rt_light_buffer.size)
		rt_shade_light(hit, &scene->rt_light_buffer, i++, rgb);
}
