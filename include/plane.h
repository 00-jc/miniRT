/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:29:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/04 21:35:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "primitives.h"

typedef struct s_RTPlane
{
	t_3dcoords	coords;
	t_3dcoords	axis;
	t_u32a		color;
}	t_RTPlane;

# ifdef __clang__

typedef struct s_RTPlaneBuffer
{
	size_t												size;
	t_3dcoords __attribute__	((counted_by(size)))	*coords;
	t_3dcoords __attribute__	((counted_by(size)))	*axis;
	t_u32a __attribute__	((counted_by(size)))		*color;
}	t_RTPlaneBuffer;

# else

typedef struct s_RTPlaneBuffer
{
	size_t		size;
	t_3dcoords	*coords;
	t_3dcoords	*axis;
	t_u32a		*color;
}	t_RTPlaneBuffer;

# endif

#endif
