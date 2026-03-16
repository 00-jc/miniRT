/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:29:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/16 20:59:26 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PLANE_H
# define RT_PLANE_H

# include "math.h"
# include "rt_parser/rt_bmp.h"

typedef struct s_RTPlane
{
	t_3dcoords	coords;
	t_3dcoords	axis;
	t_u32a		color;
	t_RTTexture	*tx;
}	t_RTPlane;

# ifdef __clang__

typedef struct s_RTPlaneBuffer
{
	size_t												size;
	t_3dcoords __attribute__	((counted_by(size)))	*coords;
	t_3dcoords __attribute__	((counted_by(size)))	*axis;
	t_u32a __attribute__	((counted_by(size)))		*color;
	t_RTTexture											**tx;
}	t_RTPlaneBuffer;

# else

typedef struct s_RTPlaneBuffer
{
	size_t		size;
	t_3dcoords	*coords;
	t_3dcoords	*axis;
	t_u32a		*color;
	t_RTTexture	**tx;
}	t_RTPlaneBuffer;

# endif

#endif
