/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 22:15:13 by asoria            #+#    #+#             */
/*   Updated: 2026/04/06 17:48:44 by jaicastr         ###   ########.fr       */
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

__attribute__((__nonnull__(1, 2, 3)))
static inline t_taggedresult	rt_try_path_cone(t_RTContext *ctx,
	t_tokenizer *t, t_RTCone *cn)
{
	t_RTTexture	*tx;
	t_RTColortx	*cx;

	tx = rt_parse_path_bmp(ctx, t);
	if ((t_uptr)tx == BMP_ERROR)
		return (KO);
	cn->tx = tx;
	cx = rt_parse_path_color(ctx, t);
	if ((t_uptr)cx == BMP_ERROR)
		return (KO);
	cn->cx = cx;
	return (OK);
}

static inline t_RTCone	rt__cn(t_3dcoords coords, t_3dcoords axis,
	t_2packd wh, t_u32a color)
{
	return ((t_RTCone){
		.coords = coords,
		.axis = axis,
		.wh = wh,
		.color = color,
	});
}

__attribute__((__always_inline__, __nonnull__(1, 2)))
static inline t_taggedresult	rt__parse_cone_wh(t_tokenizer *t,
		t_double_res wh[2])
{
	wh[0] = rt_parse_double(t);
	if (wh[0].res == KO)
		return (KO);
	wh[1] = rt_parse_double(t);
	if (wh[1].res == KO)
		return (KO);
	return (OK);
}

/*
*	cone format (label "co"):
*	co  <apex_x,apex_y,apex_z>  <ax,ay,az>  <diameter>  <height>  <R,G,B>
*	axis must be a unit vec
*	diameter and height must be positive
*/
__attribute__((__nonnull__(1, 2)))
t_taggedresult	rt_parse_cone(t_RTContext *ctx, t_tokenizer *t, t_vec *cn_vec)
{
	t_coord_result	co;
	t_coord_result	a;
	t_double_res	wh[2];
	t_color_result	c;
	t_RTCone		cn;

	(void)ctx;
	co = rt_parse_coords(t);
	if (co.res == KO)
		return (KO);
	a = rt_parse_coords(t);
	if (a.res == KO)
		return (KO);
	if (!rt__parse_cone_wh(t, wh))
		return (KO);
	if (!rt__ensure_normalized(a.coord))
		return (rt_error(NNORM), KO);
	c = rt_parse_color(t);
	if (c.res == KO)
		return (KO);
	cn = rt__cn(co.coord, a.coord, (t_2packd){wh[0].d, wh[1].d}, c.color);
	if (rt_try_path_cone(ctx, t, &cn) == KO)
		return (KO);
	return (ft_vec_push_back(cn_vec, (void *){&cn}, sizeof(cn)));
}
