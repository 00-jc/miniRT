/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cone.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/05 19:26:39 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_CONE_H
# define RT_CONE_H

# include "math.h"
# include "rt_parser/rt_bmp.h"

/*
* coords : apex of the cone
* axis   : normalised direction from apex toward the base
* wh     : x = base diameter, y = height
* color  : packed RGB (0x00RRGGBB)
*/

typedef struct s_RTCone
{
	t_3dcoords	coords;
	t_3dcoords	axis;
	t_2packd	wh;
	t_u32a		color;
	t_RTTexture	*tx;
	t_RTColortx	*cx;
}	t_RTCone;

# ifdef __clang__

typedef struct s_RTConeBuffer
{
	size_t												size;
	t_3dcoords __attribute__	((counted_by(size)))	*coords;
	t_3dcoords __attribute__	((counted_by(size)))	*apex;
	t_3dcoords __attribute__	((counted_by(size)))	*axis;
	t_2packd __attribute__		((counted_by(size)))	*wh;
	double __attribute__		((counted_by(size)))	*k;
	double __attribute__		((counted_by(size)))	*m;
	t_u32a __attribute__		((counted_by(size)))	*color;
	t_RTTexture								*restrict	tx;
	t_RTColortx								*restrict	cx;
}	t_RTConeBuffer;

# else

typedef struct s_RTConeBuffer
{
	size_t					size;
	t_3dcoords				*coords;
	t_3dcoords				*apex;
	t_3dcoords				*axis;
	t_2packd				*wh;
	double					*k;
	double					*m;
	t_u32a					*color;
	t_RTTexture	*restrict	tx;
	t_RTColortx	*restrict	cx;
}	t_RTConeBuffer;

# endif

#endif
