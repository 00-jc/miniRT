/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:38:59 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/15 04:06:47 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"
#include "private/ft_p_math.h"

__attribute__((__always_inline__, const))
static inline t_u32a	rt__ensure_normalized(t_3dcoords axis)
{
	t_v4di	vec4;

	vec4.d = *(const t_v4da * restrict const) & axis;
	vec4.d = ((vec4.d - 1.0) <= 0.0) & (vec4.d >= 0.0);
	return (vec4.i[0] == V4_CMP_OK
		&& vec4.i[1] == V4_CMP_OK
		&& vec4.i[2] == V4_CMP_OK);
}

static inline t_RTCylinder	rt__cy(t_3dcoords coords, t_3dcoords axis,
	t_2packd wh, t_u32a color)
{
	return ((t_RTCylinder){
		.coords = coords,
		.axis = axis,
		.wh = wh,
		.color = color,
	});
}

/*
 *	There was no way to fit this in 25 lines without the
 *	1-char names, sorry.
 */

__attribute__((__nonnull__(1, 2)))
t_taggedresult	rt_parse_cylinder(t_tokenizer *t, t_vec *cy_vec)
{
	t_coord_result	co;
	t_coord_result	a;
	t_double_res	wh[2];
	t_color_result	c;
	t_RTCylinder	cy;

	co = rt_parse_coords(t);
	if (co.res == KO)
		return (KO);
	a = rt_parse_coords(t);
	if (a.res == KO)
		return (KO);
	a.coord = ft_3dunit(a.coord);
	if (!rt__ensure_normalized(a.coord))
		return (rt_error(NNORM), KO);
	wh[0] = rt_parse_double(t);
	wh[1] = rt_parse_double(t);
	if (wh[0].res == KO || wh[1].res == KO)
		return (KO);
	c = rt_parse_color(t);
	if (c.res == KO)
		return (KO);
	cy = rt__cy(co.coord, a.coord, (t_2packd){wh[0].d, wh[1].d}, c.color);
	return (ft_vec_push_back(cy_vec, (void *){&cy}, sizeof(cy)));
}
