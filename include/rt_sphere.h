/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:28:49 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/16 21:01:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SPHERE_H
# define RT_SPHERE_H

# include "math.h"
# include "rt_parser/rt_bmp.h"

typedef struct s_RTSphere
{
	t_3dcoords	coords;
	double		diameter;
	t_u32a		color;
	t_RTTexture	*tx;
}	t_RTSphere;

# ifdef __clang__

typedef struct s_RTSphereBuffer
{
	size_t												size;
	t_3dcoords __attribute__	((counted_by(size)))	*coords;
	double __attribute__	((counted_by(size)))		*diameter;
	t_u32a __attribute__	((counted_by(size)))		*color;
	t_RTTexture											**tx;
}	t_RTSphereBuffer;

# else

typedef struct s_RTSphereBuffer
{
	size_t		size;
	t_3dcoords	*coords;
	double		*diameter;
	t_u32a		*color;
	t_u32a		*bitmaptx;
	t_RTTexture	**tx;
}	t_RTSphereBuffer;

# endif
#endif
