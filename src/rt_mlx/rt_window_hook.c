/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_window_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:55:24 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/18 03:33:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_mlx/rt_mlx.h"
#include "hint.h"
#define ALERR "Error\nCannot allocate image\n"

__attribute__((__nonnull__(1), hot))
int	rt_window_hook(t_RTstate *restrict const state)
{
	XWindowAttributes	attr;

	XGetWindowAttributes(
		((t_xvar *)state->ctx.rt_mlx)->display,
		((t_win_list *)state->ctx.rt_mlx_win)->window,
		&attr
		);
	if (state->ctx.display_height != (size_t)attr.height
		|| state->ctx.display_width != (size_t)attr.width)
	{
		state->ctx.display_height = 1ULL << (64
				- ft_memclz_u64((size_t)attr.height - 1));
		state->ctx.display_width = 1ULL << (64
				- ft_memclz_u64((size_t)attr.width - 1));
		state->ctx.scene_redraw = 1;
		state->ctx.rt_img->image->data = NULL;
		ft_arena_rewind(&state->ctx.rt_arena, state->ctx.rewind_image);
		XDestroyImage(state->ctx.rt_img->image);
		XFreePixmap(((t_xvar *)state->ctx.rt_mlx)->display,
			state->ctx.rt_img->pix);
		state->ctx.rt_img = NULL;
		if (rt_alloc_imagebuffer(&state->ctx) == KO)
			(rt_free_state(state), ft_pin_invariant_msg(0, (char *)ALERR));
	}
	return (0);
}
