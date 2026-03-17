/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:08:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/17 17:27:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "cstr.h"
#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"
#include "rt_mlx/rt_mlx.h"
#include <X11/X.h>

__attribute__((__always_inline__, __nonnull__(1)))
inline t_taggedresult	rt_mlx_setup(t_RTstate *state)
{
	state->ctx.rt_mlx_win = mlx_new_window(state->ctx.rt_mlx,
			(int)state->ctx.display_width, (int)state->ctx.display_height,
			(char *)"miniRT");
	if (!state->ctx.rt_mlx_win)
		return (rt_error("Error\nmlx window\n"), KO);
	mlx_hook(state->ctx.rt_mlx_win, KeyPress,
		KeyPressMask, rt_key_press, state);
	mlx_hook(state->ctx.rt_mlx_win, KeyRelease,
		KeyReleaseMask, rt_key_release, state);
	mlx_hook(state->ctx.rt_mlx_win, DestroyNotify,
		NoEventMask, rt_killprocess, state);
	mlx_hook(state->ctx.rt_mlx_win, MotionNotify,
		PointerMotionMask, rt_handle_mouse_move, state);
	mlx_loop_hook(state->ctx.rt_mlx, rt_render_hotloop, state);
	return (OK);
}

__attribute__((__always_inline__))
static inline t_RTstate	rt_init_state(void)
{
	t_map		map;
	t_arena		arena;
	t_RTstate	state;
	void		*mlx;

	state = (t_RTstate){0};
	arena = ft_new_arena_alloc();
	if (!arena.current)
		return (state);
	map = ft_map_new();
	if (!map.buckets)
		return (ft_destroy_arena(&arena), state);
	mlx = mlx_init();
	if (!mlx)
		return (ft_map_destroy(&state.ctx.loaded_textures),
			ft_destroy_arena(&arena), state);
	state = (t_RTstate){.ctx.rt_arena = arena, .ctx.rt_mlx = mlx,
		.ctx.rewind_render = ft_arena_checkpoint(&arena),
		.ctx.loaded_textures = map};
	return (state);
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	rt_free_state(t_RTstate *state)
{
	if (state->ctx.rt_img && state->ctx.rt_img->image)
	{
		state->ctx.rt_img->image->data = NULL;
		XDestroyImage(state->ctx.rt_img->image);
		XFreePixmap(((t_xvar *)state->ctx.rt_mlx)->display,
			state->ctx.rt_img->pix);
	}
	if (state->ctx.rt_mlx_win)
		mlx_destroy_window(state->ctx.rt_mlx, state->ctx.rt_mlx_win);
	ft_destroy_arena(&state->ctx.rt_arena);
	ft_map_destroy(&state->ctx.loaded_textures);
	if (state->ctx.pool.tp.alive)
		ft_threadpool_destroy(&state->ctx.pool.tp, FT_NTHREADS);
	free(state->ctx.rt_mlx);
}

__attribute__((__nonnull__(1), __always_inline__))
inline t_taggedresult	rt_load_state(t_RTstate *state)
{
	size_t	len;

	len = ft_strlen(state->ctx.rt_argv[1]);
	if (len <= 3 || ft_memcmp(&state->ctx.rt_argv[1][len - 3], ".rt", 3) != 0)
		return (rt_error("Error\nFile must end in .rt\n"), KO);
	if (!rt_parse_file_into_state(state, state->ctx.rt_argv[1],
			&state->ctx.rt_arena))
		return (KO);
	return (OK);
}

int	main(int argc, char **argv)
{
	static t_RTstate	state = {0};

	if (argc < 2)
		return (rt_error(USAGE, argv[0]), EXIT_FAILURE);
	state = rt_init_state();
	state.ctx.rt_argv = argv;
	state.ctx.rt_argc = argc;
	if (!state.ctx.rt_arena.current)
		return (rt_error("Error\narena init\n"), EXIT_FAILURE);
	state.ctx.pool.arg = (t_thread_arg){.tp = &state.ctx.pool.tp,
		.external_state = &state, .fn = rt_threadrt};
	if (!ft_threadpool_new(&state.ctx.pool.tp, &state.ctx.pool.arg))
		return (rt_error("Error\nThreadpool init\n"), rt_free_state(&state),
			EXIT_FAILURE);
	if (rt_load_state(&state) == KO || !rt_parse_display_size(state.ctx.rt_argc,
			&state.ctx, (const char **)state.ctx.rt_argv)
		|| !rt_mlx_setup(&state) || !rt_alloc_imagebuffer(&state.ctx))
		return (rt_free_state(&state), EXIT_FAILURE);
	mlx_loop(state.ctx.rt_mlx);
}
