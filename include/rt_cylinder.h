/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cylinder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:29:34 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/16 20:58:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_CYLINDER_H
# define RT_CYLINDER_H

# include "math.h"
# include "rt_parser/rt_bmp.h"

typedef struct s_RTCylinder
{
	t_3dcoords	coords;
	t_3dcoords	axis;
	t_2packd	wh;
	t_u32a		color;
	t_RTTexture	*tx;
}	t_RTCylinder;

# ifdef __clang__

typedef struct s_RTCylinderBuffer
{
	size_t												size;
	t_3dcoords __attribute__	((counted_by(size)))	*coords;
	t_3dcoords __attribute__	((counted_by(size)))	*axis;
	t_2packd __attribute__	((counted_by(size)))		*wh;
	t_u32a __attribute__	((counted_by(size)))		*color;
	t_RTTexture											**tx;
}	t_RTCylinderBuffer;

# else

typedef struct s_RTCylinderBuffer
{
	size_t		size;
	t_3dcoords	*coords;
	t_3dcoords	*axis;
	t_2packd	*wh;
	t_u32a		*color;
	t_RTTexture	**tx;
}	t_RTCylinderBuffer;

# endif

#endif
