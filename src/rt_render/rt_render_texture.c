/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:55:53 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/17 20:13:33 by jaicastr         ###   ########.fr       */
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

	x = (size_t)(u * (double)tx->width) & (tx->width - 1);
	y = (size_t)(v * (double)tx->height) & (tx->height - 1);
	return (tx->data[(y << (63 - ft_memclz_u64(tx->width))) | x] * INV_255);
}

__attribute__((__nonnull__(3), __always_inline__, pure))
inline t_u32a	rt_sample_color(double u, double v, t_RTColortx *cx)
{
	size_t	x;
	size_t	y;

	x = (size_t)(u * (double)cx->width) & (cx->width - 1);
	y = (size_t)(v * (double)cx->height) & (cx->height - 1);
	return (cx->data[(y << (63 - ft_memclz_u64(cx->width))) | x]);
}
