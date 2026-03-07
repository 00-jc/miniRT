/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 01:11:52 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 02:21:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"
#include "private/ft_p_math.h"

#define V4_CMP_OK 0xFFFFFFFFFFFFFFFFULL

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

__attribute__((__nonnull__(1, 2)))
t_taggedresult	rt_parse_plane(t_tokenizer *t, t_vec *plane_vec)
{
	t_coord_result	coords;
	t_coord_result	axis;
	t_color_result	color;
	t_RTPlane		plane;

	coords = rt_parse_coords(t);
	if (coords.res == KO)
		return (KO);
	axis = rt_parse_coords(t);
	if (axis.res == KO)
		return (KO);
	if (!rt__ensure_normalized(axis.coord))
		return (rt_error(NNORM), KO);
	color = rt_parse_color(t);
	if (color.res == KO)
		return (KO);
	plane = (t_RTPlane){.color = color.color, .axis = axis.coord,
		.coords = coords.coord};
	return (ft_vec_push_back(plane_vec, (void *){&plane}, sizeof(plane)));
}
