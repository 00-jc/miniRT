/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_hotloop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:20:46 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/12 11:28:58 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_render/rt_render.h"
#include "rt_miniRT.h"

__attribute__((__nonnull__(1)))
static inline t_taggedresult	rt_reload(t_RTstate *state)
{
	if (!state->ctx.reload)
		return (OK);
	state->ctx.rt_arena.current->used = 0;
	state->scene = (t_RTScene){0};
	state->ctx.rt_img->image->data = NULL;
	XDestroyImage(state->ctx.rt_img->image);
	XFreePixmap(((t_xvar *)state->ctx.rt_mlx)->display,
		state->ctx.rt_img->pix);
	state->ctx.rt_img = NULL;
	if (rt_load_state(state) == KO
		|| !rt_alloc_imagebuffer(&state->ctx))
		return (KO);
	state->ctx.reload = 0;
	state->ctx.scene_redraw = 1;
	return (OK);
}

__attribute__((__nonnull__(1), hot))
int	rt_render_hotloop(t_RTstate *state)
{
	if (rt_reload(state) == KO)
		(rt_free_state(state), exit(EXIT_FAILURE));
	if (state->ctx.scene_redraw)
	{
		ft_arena_rewind(&state->ctx.rt_arena, state->ctx.rewind_render);
		rt_putimg(&state->ctx);
	}
	return ((int)(state->ctx.scene_redraw = 0));
}
