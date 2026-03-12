/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:08:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/12 03:20:26 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"
#include "rt_mlx/rt_mlx.h"

__attribute__((__always_inline__, __nonnull__(1)))
inline t_taggedresult	rt_mlx_setup(t_RTstate *state)
{
	state->ctx.rt_mlx_win = mlx_new_window(state->ctx.rt_mlx,
			(int)state->ctx.display_width, (int)state->ctx.display_height,
			(char *)"miniRT");
	if (!state->ctx.rt_mlx_win)
		return (rt_error("Error\nmlx window\n"), KO);
	mlx_hook(state->ctx.rt_mlx_win, 2, 1L << 0, rt_key_press, state);
	mlx_hook(state->ctx.rt_mlx_win, 3, 1L << 1, rt_key_release, state);
	mlx_hook(state->ctx.rt_mlx_win, 6, 1L << 6, rt_handle_mouse_move, state);
	mlx_loop_hook(state->ctx.rt_mlx, rt_key_hook, state);
	mlx_loop_hook(state->ctx.rt_mlx, rt_render_hotloop, state);
	return (OK);
}

__attribute__((__always_inline__))
static inline t_RTstate	rt_init_state(void)
{
	t_arena		arena;
	t_RTstate	state;
	void		*mlx;

	state = (t_RTstate){0};
	arena = ft_new_arena_alloc();
	if (!arena.current)
		return (state);
	mlx = mlx_init();
	if (!mlx)
		return (ft_destroy_arena(&arena), state);
	state = (t_RTstate){.ctx.rt_arena = arena, .ctx.rt_mlx = mlx};
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
	free(state->ctx.rt_mlx);
}

__attribute__((__nonnull__(1), __always_inline__))
inline t_taggedresult	rt_load_state(t_RTstate *state)
{
	if (!rt_parse_file_into_state(&state->scene, state->ctx.rt_argv[1],
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
	if (rt_load_state(&state) == KO || !rt_parse_display_size(state.ctx.rt_argc,
			&state.ctx, (const char **)state.ctx.rt_argv)
		|| !rt_mlx_setup(&state) || !rt_alloc_imagebuffer(&state.ctx))
		return (rt_free_state(&state), EXIT_FAILURE);
	mlx_loop(state.ctx.rt_mlx);
}
