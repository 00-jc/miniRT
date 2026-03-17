/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:55:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/17 18:52:41 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_parser/rt_bmp.h"
#include "rt_render/rt_render.h"

__attribute__((__nonnull__(3), __always_inline__, pure))
inline double	rt_sample(double u, double v, t_RTTexture *tx)
{
	size_t	x;
	size_t	y;

	x = (size_t)(u * (double)tx->width);
	y = (size_t)(v * (double)tx->height);
	return (tx->data[(y % tx->height) * tx->width + (x % tx->width)] * INV_255);
}

__attribute__((__nonnull__(3), __always_inline__, pure))
inline t_u32a	rt_sample_color(double u, double v, t_RTColortx *cx)
{
	size_t	x;
	size_t	y;
	size_t	idx;

	x = (size_t)(u * (double)cx->width);
	y = (size_t)(v * (double)cx->height);
	idx = ((y % cx->height) * cx->width + (x % cx->width));
	return (cx->data[idx]);
}
