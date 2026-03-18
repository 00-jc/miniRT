/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_hotloop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:20:46 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/17 23:57:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_mlx/rt_mlx.h"
#include "rt_render/rt_render.h"
#include "rt_miniRT.h"
#include <sys/time.h>

__attribute__((__nonnull__(1), __always_inline__, hot))
static inline void	rt_init_vp(t_RTstate *state)
{
	const t_3dcoords		yax = (t_3dcoords){0, 1, 0, 0};
	static t_u8				init = 0;

	if (!init || state->ctx.reload)
	{
		state->ctx.vp.scale = __builtin_tan((double)state->scene.rt_camera.fov
				* (0.0027777777 * RT_PI));
		state->ctx.vp.aspect = (double)state->ctx.display_width
			/ (double)state->ctx.display_height;
		state->ctx.vp.width = state->ctx.display_width;
		state->ctx.vp.height = state->ctx.display_height;
		state->ctx.vp.inv_width = 1 / (double)state->ctx.display_width;
		state->ctx.vp.inv_height = 1 / (double)state->ctx.display_height;
		init = 1;
		state->ctx.reload = 0;
	}
	state->ctx.vp.right = ft_3dunit(ft_3dcross(state->scene.rt_camera.axis,
				yax));
	state->ctx.vp.up = ft_3dunit(ft_3dcross(state->ctx.vp.right,
				state->scene.rt_camera.axis));
	state->ctx.vp.forward = state->scene.rt_camera.axis;
}

__attribute__((__nonnull__(1), __always_inline__, hot))
static inline t_taggedresult	rt_reload(t_RTstate *state)
{
	if (!state->ctx.reload)
		return (OK);
	state->scene = (t_RTScene){0};
	state->ctx.rt_img->image->data = NULL;
	ft_arena_rewind(&state->ctx.rt_arena, state->ctx.rewind_render);
	ft_map_clear(&state->ctx.loaded_textures);
	XDestroyImage(state->ctx.rt_img->image);
	XFreePixmap(((t_xvar *)state->ctx.rt_mlx)->display,
		state->ctx.rt_img->pix);
	state->ctx.rt_img = NULL;
	if (rt_load_state(state) == KO
		|| !rt_alloc_imagebuffer(&state->ctx))
		return (KO);
	return (OK);
}

__attribute__((__nonnull__(1), hot))
int	rt_render_hotloop(t_RTstate *state)
{
	rt_key_hook(state);
	if (rt_reload(state) == KO)
		(rt_free_state(state), exit(EXIT_FAILURE));
	state->ctx.scene_redraw |= (state->keys != 0);
	if (state->ctx.scene_redraw)
	{
		rt_init_vp(state);
		state->ctx.pool.current_tile = 0;
		ft_threadpool_start(&state->ctx.pool.tp);
		ft_threadpool_wait(&state->ctx.pool.tp);
		rt_putimg(&state->ctx);
	}
	return ((int)(state->ctx.scene_redraw = 0));
}
