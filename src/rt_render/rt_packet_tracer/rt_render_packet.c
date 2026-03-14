/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_packet.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 16:08:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/14 19:32:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "private/ft_p_math.h"
#include "rt_render/rt_render.h"

#define RT_U 0
#define RT_R 1
#define RT_F 2

__attribute__((hot, const, __always_inline__))
inline t_3dcoordsx8	rt_v8_to_coords(t_v8da v)
{
	return ((t_3dcoordsx8)
		{
			.a = {v[0], v[0], v[0], 0},
			.b = {v[1], v[1], v[1], 0},
			.c = {v[2], v[2], v[2], 0},
			.d = {v[3], v[3], v[3], 0},
			.e = {v[4], v[4], v[4], 0},
			.f = {v[5], v[5], v[5], 0},
			.g = {v[6], v[6], v[6], 0},
			.h = {v[7], v[7], v[7], 0},
		});
}

__attribute__((hot, const, __always_inline__))
inline t_3dcoordsx8	rt_coordbroadcast(t_3dcoords c)
{
	return ((t_3dcoordsx8)
		{
			.a = c,
			.b = c,
			.c = c,
			.d = c,
			.e = c,
			.f = c,
			.g = c,
			.h = c,
		});
}

__attribute__((__always_inline__, __nonnull__(1), pure, hot))
inline t_RTPacket	rt_render_packet(t_RTScene *scene, t_RTContext *ctx,
	size_t x, size_t y)
{
	t_RTPacket		packet;
	t_v8da			dx;
	t_v8da			dy;
	t_3dcoordsx8	coords[3];

	packet = (t_RTPacket){0};
	dx = (t_v8da){(double)x, (double)(x + 1), (double)(x + 2),
		(double)(x + 3), (double)(x + 4), (double)(x + 5), (double)(x + 6),
		(double)(x + 7)};
	dy = (t_v8da){(double)y, (double)y, (double)y, (double)y,
		(double)y, (double)y, (double)y, (double)y};
	packet.origin = rt_coordbroadcast(scene->rt_camera.coords);
	dx = (2.0 * (dx + 0.5) * (double)ctx->vp.inv_width - 1.0)
		* ctx->vp.aspect * ctx->vp.scale;
	dy = (1.0 - 2.0 * (dy + 0.5) * (double)ctx->vp.inv_height) * ctx->vp.scale;
	coords[RT_F] = rt_coordbroadcast(ctx->vp.forward);
	coords[RT_R] = rt_coordbroadcast(ctx->vp.right);
	coords[RT_U] = rt_coordbroadcast(ctx->vp.up);
	packet.dir = ft_3dunit8(ft_3dadd8(coords[RT_F],
				ft_3dadd8(ft_3dmul8(coords[RT_R], rt_v8_to_coords(dx)),
					ft_3dmul8(coords[RT_U], rt_v8_to_coords(dy)))));
	return (packet);
}
