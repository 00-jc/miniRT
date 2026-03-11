/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_miniRT.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:07:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/11 02:02:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MINIRT_H
# define RT_MINIRT_H

# include "mlx.h"
# include "alloc.h"
# include "types.h"
# include "rt_sphere.h"
# include "rt_cylinder.h"
# include "rt_plane.h"
# include "rt_light.h"
# include "rt_camera.h"
# include <pthread.h>

/* @ compile-time this should be passed
 * like: -DRT_NTHREADS=$$(nproc) or something
 * along those lines */

# ifndef RT_NTHREADS
#  define RT_NTHREADS 16
# endif

/* we should be mindful of _what_ do we pass around to
 * the functions too, if we're not careful with all this
 * conf well pollute every cache line we have, rule of thumb:
 *
 * - t_RTScene: 		for the render inner loops (all threads).
 * - t_RTThreadpool: 	for the outer render loop.
 * - t_RTContext: 		for the outer render loop.
 *
 * NOTE: all these structs actually live on main's stack
 * and dynamic allocs happen in the arena, which also lives
 * in main's stack frame :P.
 */

/* hot (accesses mid-render) */
typedef struct s_RTScene
{
	t_RTCylinderBuffer		rt_cylinder_buffer;
	t_RTPlaneBuffer			rt_plane_buffer;
	t_RTSphereBuffer		rt_sphere_buffer;
	t_RTLightBuffer			rt_light_buffer;
	t_RTAmbientLight		rt_ambient;
	t_RTCamera				rt_camera;
} __attribute__((aligned(64)))	t_RTScene;

/* cold (should be accesed once per frame on start & end) */
typedef struct s_RTThreadPool
{
	pthread_t			threads[RT_NTHREADS];
	pthread_mutex_t		mutex;
	pthread_cond_t		start;
	pthread_cond_t		stop;
	size_t				ntiles;
	size_t				current_tile;
	t_u32a				kill_switch;
	t_u32a				working;
}	t_RTThreadPool;

/* cold (should be accesed once per frame on flush) */
typedef struct s_RTContext
{
	size_t		display_width;
	size_t		display_height;
	void		*rt_mlx_win;
	t_u32a		*frame_buffer;
	t_arena		rt_arena;
	void		*rt_mlx;
	t_u32a		scene_is_dirty;
}	t_RTContext;

/* cold, only lives in main */
typedef struct s_RTstate
{
	t_RTScene				scene;
	t_RTContext				ctx;
	t_RTThreadPool			thread_pool;
}	t_RTstate;

void	rt_free_state(t_RTstate *state)\
			__attribute__((__nonnull__(1)));

#endif
