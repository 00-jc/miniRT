/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:36:16 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/12 18:40:09 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_H
# define RT_RENDER_H

# include "types.h"
# include "mlx.h"
# include "mlx_int.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <X11/extensions/XShm.h>
# include <X11/XKBlib.h>
# include "rt_parser/rt_parser.h"

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

typedef struct	S_RTHit
{
	t_3dcoords	point;
	t_3dcoords	normal;
	double		t;
	t_u32a		color;
}	t_RTHit;

__attribute__((__nonnull__(1, 2), __hot__))
void	rt_render_frame(t_RTContext	*ctx, t_RTScene *scene);

__attribute__((__nonnull__(3, 4), __hot__))
t_RTRay	rt_camera_ray(size_t x, size_t y, t_RTContext *ctx, t_RTScene *scene);

__attribute__((__nonnull__(3, 4), hot))
t_u32a	rt_cast_ray(size_t x, size_t y, t_RTContext *ctx, t_RTScene *scene);

#endif
