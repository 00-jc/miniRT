/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/17 15:06:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RENDER_TYPES_H
# define RT_RENDER_TYPES_H

# include "types.h"
# include "math.h"
# include "mlx.h"
# include "rt_parser/rt_bmp.h"
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <sys/shm.h>
# include <X11/extensions/XShm.h>
# define MLX_TYPE_XIMAGE 1
# define MLX_MAX_EVENT LASTEvent
# define RT_PACKETSIZE 8

typedef __attribute__((vector_size(32), aligned(1), __may_alias__)) t_u32a\
																	t_colorlane;
typedef struct s_event_list
{
	int		mask;
	int		(*hook)();
	void	*param;
}				t_event_list;

typedef struct s_win_list
{
	Window				window;
	GC					gc;
	struct s_win_list	*next;
	int					(*mouse_hook)();
	int					(*key_hook)();
	int					(*expose_hook)();
	void				*mouse_param;
	void				*key_param;
	void				*expose_param;
	t_event_list		hooks[MLX_MAX_EVENT];
}				t_win_list;

typedef struct s_xvar
{
	Display		*display;
	Window		root;
	int			screen;
	int			depth;
	Visual		*visual;
	Colormap	cmap;
	int			private_cmap;
	t_win_list	*win_list;
	int			(*loop_hook)();
	void		*loop_param;
	int			use_xshm;
	int			pshm_format;
	int			do_flush;
	int			decrgb[6];
	Atom		wm_delete_window;
	Atom		wm_protocols;
	int			end_loop;
}				t_xvar;

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
	t_3dcoords	view_dir;
	double		t;
	double      uv[2];
	t_RTTexture	*tx;
	t_u32a		color;
}	t_RTHit;

typedef struct s_RTViewport
{
	double		scale;
	double		aspect;
	double		inv_width;
	double		inv_height;
	size_t		width;
	size_t		height;
	t_3dcoords	right;
	t_3dcoords	up;
	t_3dcoords	forward;
}	t_RTViewport;

#endif
