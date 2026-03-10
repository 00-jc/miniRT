/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:08:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/10 15:16:33 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_parser/rt_parser.h"
#include "rt_logger/rt_errors.h"

/*	MINIRT WORKFLOW CHART:
	- init arena and state
	- start threadpool and lock it
	- parse the .rt file, allocate the SoA in the state
	- hook to mlx
	- on loop():
		- rewind the arena to the last frame scope
		- build bvhs {
			- 1 bvh per element type (test 8 rays x element w/simd
			  + packet tracing)
			- each thread tests 2-4 short trees
			- to reuse:
				- scene_is_dirty variable
		}
		- signals threads to start
		- threads build a frame
		- on input (mlx hook):
			- set threads to stop()
			- goto loop()
 */

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
static inline void	rt_free_state(t_RTstate *state)
{
	ft_destroy_arena(&state->ctx.rt_arena);
	free(state->ctx.rt_mlx);
}

int	main(int argc, char **argv)
{
	t_RTstate	state;

	if (argc != 2)
		return (rt_error(USAGE, argv[0]), EXIT_FAILURE);
	state = rt_init_state();
	if (!state.ctx.rt_arena.current)
		return (rt_error("Error\narena init\n"), EXIT_FAILURE);
	if (!rt_parse_file_into_state(&state.scene, argv[1], &state.ctx.rt_arena))
		return (rt_free_state(&state), EXIT_FAILURE);
	rt_free_state(&state);
	return (EXIT_SUCCESS);
}
