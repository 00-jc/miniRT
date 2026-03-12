/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_hotloop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:20:46 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/12 02:24:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hint.h"
#include "rt_miniRT.h"

__attribute__((__nonnull__(1), hot))
int		rt_render_hotloop(t_RTstate *state)
{
	if (state->ctx.scene_is_dirty)
	{
		if (state->ctx.rt_img && state->ctx.rt_img->image)
		{
			state->ctx.rt_img->image->data = NULL;
			XDestroyImage(state->ctx.rt_img->image);
			XFreePixmap(((t_xvar *)state->ctx.rt_mlx)->display,
				state->ctx.rt_img->pix);
			state->ctx.rt_img = NULL;
		}
		if (state->ctx.rewind_render.location)
			ft_arena_rewind(&state->ctx.rt_arena, state->ctx.rewind_render);
		if (rt_alloc_imagebuffer(&state->ctx) == KO)
			(rt_free_state(state), ft_pin_invariant(0));
	}
	if (state->ctx.scene_redraw)
	{

	}
	rt_putimg(&state->ctx);
	return ((int)(state->ctx.scene_is_dirty = 0));
}
