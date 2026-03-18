/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:36:58 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/18 00:43:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_parser/rt_parser.h"

__attribute__((__nonnull__(1), __always_inline__))
inline t_taggedresult	rt_alloc_imagebuffer(t_RTContext *ctx)
{
	t_xvar	*xvar;
	t_RTImg	*img;

	xvar = ctx->rt_mlx;
	ctx->buffersize = (ctx->display_height * (ctx->display_width + 32)) << 2;
	img = ft_arena_alloc(&ctx->rt_arena, ctx->buffersize + sizeof(t_RTImg), 16);
	if (!img)
		return (ft_arena_rewind(&ctx->rt_arena, ctx->rewind_render), KO);
	*img = (t_RTImg){.width = (int)ctx->display_width,
		.height = (int)ctx->display_height, .type = MLX_TYPE_XIMAGE,
		.format = ZPixmap, .gc = 0, .pix = XCreatePixmap(xvar->display,
			xvar->root, (int)ctx->display_width,
			(int)ctx->display_height, xvar->depth)
	};
	ft_memset(img->data, 0x00, ctx->buffersize);
	ctx->pix_num = ctx->display_height * ctx->display_width;
	img->image = XCreateImage(xvar->display, xvar->visual, xvar->depth, ZPixmap,
			0, (void *)img->data, (int)ctx->display_width,
			(int)ctx->display_height, 32, 0);
	if (!img->image)
		return (ft_arena_rewind(&ctx->rt_arena, ctx->rewind_render), KO);
	img->size_line = img->image->bytes_per_line;
	img->bpp = img->image->bits_per_pixel;
	ctx->scene_redraw = 1;
	return ((void)(ctx->rt_img = img), OK);
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	rt_putimg(t_RTContext *ctx)
{
	t_xvar		*xvar;
	t_win_list	*win;
	t_RTImg		*img;

	xvar = ctx->rt_mlx;
	img = ctx->rt_img;
	win = ctx->rt_mlx_win;
	XPutImage(xvar->display, img->pix, win->gc, img->image,
		0, 0, 0, 0, img->width, img->height);
	XCopyArea(xvar->display, img->pix, win->window, win->gc,
		0, 0, img->width, img->height, 0, 0);
	if (xvar->do_flush)
		XFlush(xvar->display);
}
