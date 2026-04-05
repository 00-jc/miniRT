/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_cone_tx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by asoria            #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_render/rt_render.h"

__attribute__((__always_inline__))
static inline void	rt_cone_uv_cap(t_RTHit *hit,
		t_RTConeBuffer *buf, size_t i, t_3dcoords *ptb)
{
	t_3dcoords	oc;

	oc = ft_3dsub(hit->point, buf->coords[i]);
	hit->uv[0] = 0.5 + ft_3ddot(oc, ptb[0]) / buf->wh[i].x;
	hit->uv[1] = 0.5 + ft_3ddot(oc, ptb[1]) / buf->wh[i].x;
}

__attribute__((__always_inline__))
static inline void	rt_cone_uv_lat(t_RTHit *hit,
		t_RTConeBuffer *buf, size_t i, t_3dcoords *ptb)
{
	t_3dcoords	oc;
	double		proj;

	oc = ft_3dsub(hit->point, buf->apex[i]);
	proj = ft_3ddot(oc, buf->axis[i]);
	hit->uv[0] = 0.5 + __builtin_atan2(ft_3ddot(oc, ptb[1]),
			ft_3ddot(oc, ptb[0])) * 0.159154943092;
	hit->uv[1] = -proj / buf->wh[i].y;
}

__attribute__((__always_inline__, __nonnull__(1, 2)))
inline void	rt_handle_cone_tx(t_RTHit *hit, t_RTConeBuffer *buf,
		size_t i, int is_cap)
{
	t_3dcoords	ptb[2];
	t_3dcoords	ref;

	if (!buf->tx[i])
		return ;
	if (ft_fabs(buf->axis[i].y) < 0.999)
		ref = (t_3dcoords){0, 1, 0, 0};
	else
		ref = (t_3dcoords){1, 0, 0, 0};
	ptb[0] = ft_3dunit(ft_3dcross(buf->axis[i], ref));
	ptb[1] = ft_3dcross(buf->axis[i], ptb[0]);
	if (is_cap)
		rt_cone_uv_cap(hit, buf, i, ptb);
	else
		rt_cone_uv_lat(hit, buf, i, ptb);
	hit->tx = buf->tx[i];
}
