/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:28:25 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/07 16:54:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_LIGHT_H
# define RT_LIGHT_H

# include "rt_primitives.h"

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
	t_u8		is_init;
}	t_RTAmbientLight;

# ifdef __clang__

typedef struct s_RTLightBuffer
{
	size_t												size;
	t_3dcoords __attribute__	((counted_by(size)))	*coords;
	double __attribute__	((counted_by(size)))		*brightness;
	t_u32a __attribute__	((counted_by(size)))		*color;
}	t_RTLightBuffer;

# else

typedef struct s_RTLightBuffer
{
	size_t		size;
	t_3dcoords	*coords;
	double		*brightness;
	t_u32a		*color;
}	t_RTLightBuffer;

# endif

#endif
