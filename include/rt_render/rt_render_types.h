/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/12 22:52:06 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_TYPES_H
# define RT_RENDER_TYPES_H

# include "types.h"
# include "math.h"
# include "mlx.h"
# include "mlx_int.h"
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <sys/shm.h>
# include <X11/extensions/XShm.h>

typedef struct s_RTImg
{
	XImage			*image;
	Pixmap			pix;
	GC				gc;
	int				size_line;
	int				bpp;
	int				width;
	int				height;
	int				type;
	int				format;
	XShmSegmentInfo	shm;
	t_u32a			data[];
}	t_RTImg;

typedef struct s_RTRay
{
	t_3dcoords	origin;
	t_3dcoords	dir;
}	t_RTRay;

typedef struct s_RTHit
{
	t_3dcoords	point;
	t_3dcoords	normal;
	double		t;
	t_u32a		color;
}	t_RTHit;

#endif
