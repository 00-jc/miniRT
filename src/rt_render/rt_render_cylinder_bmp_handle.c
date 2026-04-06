/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_cylinder_bmp_handle.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:47:34 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/06 17:36:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_render/rt_render.h"

__attribute__((__always_inline__, __nonnull__(1)))
inline void	rt_handle_cy_tx(t_RTHit *hit, t_RTCylinderBuffer buf, size_t i)
{
	double		uvp[3];
	t_3dcoords	ptb[3];
	t_3dcoords	ref;

	if (buf.tx[i] && buf.cx[i])
	{
		ptb[0] = ft_3dsub(hit->point, buf.coords[i]);
		uvp[2] = ft_3ddot(ptb[0], buf.axis[i]);
		if (ft_fabs(buf.axis[i].y) < 0.999)
			ref = (t_3dcoords){0, 1, 0, 0};
		else
			ref = (t_3dcoords){1, 0, 0, 0};
		ptb[1] = ft_3dunit(ft_3dcross(buf.axis[i], ref));
		ptb[2] = ft_3dcross(buf.axis[i], ptb[1]);
		uvp[0] = 0.5 + __builtin_atan2(ft_3ddot(ptb[0], ptb[2]),
				ft_3ddot(ptb[0], ptb[1])) * 0.159154943092;
		uvp[1] = (uvp[2] + buf.wh[i].y * 0.5) / buf.wh[i].y;
		hit->uv[0] = uvp[0];
		hit->uv[1] = uvp[1];
		hit->tx = buf.tx[i];
	}
}
