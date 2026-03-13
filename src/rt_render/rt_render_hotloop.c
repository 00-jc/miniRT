/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_hotloop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:20:46 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/13 17:58:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_mlx/rt_mlx.h"
#include "rt_render/rt_render.h"
#include "rt_miniRT.h"
#include "math.h"
#include <sys/time.h>

extern double	tan(double x);

__attribute__((__nonnull__(1), __always_inline__, hot))
static inline void	rt_init_vp(t_RTstate *state)
{
	static t_u8		init = 0;

	if (!init || state->ctx.reload)
	{
		state->ctx.vp.scale = tan((double)state->scene.rt_camera.fov
				* (0.0027777777 * RT_PI));
		state->ctx.vp.aspect = (double)state->ctx.display_width
			/ (double)state->ctx.display_height;
		state->ctx.vp.width = state->ctx.display_width;
		state->ctx.vp.height = state->ctx.display_height;
		state->ctx.vp.inv_width = 1 / (double)state->ctx.display_width;
		state->ctx.vp.inv_height = 1 / (double)state->ctx.display_height;
		init = 1;
	}
}

__attribute__((__nonnull__(1), __always_inline__, hot))
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
	return (OK);
}

__attribute__((__nonnull__(1), hot))
int	rt_render_hotloop(t_RTstate *state)
{
	rt_init_vp(state);
	rt_key_hook(state);
	if (rt_reload(state) == KO)
		(rt_free_state(state), exit(EXIT_FAILURE));
	if (state->ctx.scene_redraw)
	{
		ft_arena_rewind(&state->ctx.rt_arena, state->ctx.rewind_render);
		rt_render_frame(&state->ctx, &state->scene);
		rt_putimg(&state->ctx);
	}
	return ((int)(state->ctx.scene_redraw = 0));
}


/*
__attribute__((__nonnull__(1), __always_inline__, hot))
inline void	rt_printfps(t_RTstate *state)
{
	struct timeval	start;
	struct timeval	end;
    long			seconds;
    long			useconds;
    double			mtime;

	gettimeofday(&start, null);
	ft_arena_rewind(&state->ctx.rt_arena, state->ctx.rewind_render);
	rt_render_frame(&state->ctx, &state->scene);
	rt_putimg(&state->ctx);
	gettimeofday(&end, null);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((double)seconds * 1000.0)
		+ ((double)useconds * 0.001);
	if (mtime > 0)
		ft_printf("fps: %f | frame time: %fms\r", 1000.0 / mtime, mtime);
}
*/
