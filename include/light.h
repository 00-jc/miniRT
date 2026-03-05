/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:28:25 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/04 21:35:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "primitives.h"

typedef struct s_RTLight
{
	t_3dcoords	coords;
	double		brightness;
	t_u32a		color;
}	t_RTLight;

typedef struct s_RTAmbientLight
{
	double		brightness;
	t_u32a		color;
}	t_RTAmbientLight;

# ifdef __clang__

typedef struct s_RTLightBuffer
{
	size_t												size;
	t_3dcoords __attribute__	((counted_by(size)))	*coords;
	double __attribute__	((counted_by(size)))		*brightness;
	t_u32a __attribute__	((counted_by(size)))		*color;
}	t_RTLightBuffer;

typedef struct s_RTAmbientLightBuffer
{
	size_t												size;
	double __attribute__	((counted_by(size)))		*brightness;
	t_u32a __attribute__	((counted_by(size)))		*color;
}	t_RTAmbientLightBuffer;

# else

typedef struct s_RTLightBuffer
{
	size_t		size;
	t_3dcoords	*coords;
	double		*brightness;
	t_u32a		*color;
}	t_RTLightBuffer;

typedef struct s_RTAmbientLightBuffer
{
	size_t		size;
	double		*brightness;
	t_u32a		*color;
}	t_RTAmbientLightBuffer;

# endif

#endif
