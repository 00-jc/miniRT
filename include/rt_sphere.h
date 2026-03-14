/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:28:49 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/14 15:55:56 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SPHERE_H
# define RT_SPHERE_H

# include "math.h"

typedef struct s_RTSphere
{
	t_3dcoords	coords;
	double		diameter;
	t_u32a		color;
}	t_RTSphere;

# ifdef __clang__

typedef struct s_RTSphereBuffer
{
	size_t												size;
	t_3dcoords __attribute__	((counted_by(size)))	*coords;
	double __attribute__	((counted_by(size)))		*diameter;
	t_u32a __attribute__	((counted_by(size)))		*color;
}	t_RTSphereBuffer;

# else

typedef struct s_RTSphereBuffer
{
	size_t		size;
	t_3dcoords	*coords;
	double		*diameter;
	t_u32a		*color;
}	t_RTSphereBuffer;

# endif
#endif
