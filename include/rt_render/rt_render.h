/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:36:16 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/11 18:35:19 by jaicastr         ###   ########.fr       */
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

#endif
