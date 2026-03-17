/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_miniRT.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:07:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/17 18:22:57 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MINIRT_H
# define RT_MINIRT_H

# include "alloc.h"
# include "types.h"
# include "rt_sphere.h"
# include "rt_cylinder.h"
# include "rt_plane.h"
# include "rt_light.h"
# include "rt_camera.h"
# include "threadpool.h"
# include "map.h"
# include <pthread.h>
# include "rt_render/rt_render_types.h"

/* @ compile-time this should be passed
 * like: -DRT_NTHREADS=$$(nproc) or something
 * along those lines */

# ifndef RT_NTHREADS
#  define RT_NTHREADS 16
# endif

# define KEY_W 1
# define KEY_A 2
# define KEY_S 4
# define KEY_D 8
# define KEY_UP 16
# define KEY_DOWN 32

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

typedef struct s_RTPool
{
	t_threadpool			tp;
	t_thread_arg			arg;
	size_t					current_tile;
}	t_RTPool;

/* cold (should be accesed once per frame on flush) */
typedef struct s_RTContext
{
	size_t				display_width;
	size_t				display_height;
	size_t				buffersize;
	size_t				pix_num;
	void				*rt_mlx_win;
	t_RTImg				*rt_img;
	t_arena				rt_arena;
	void				*rt_mlx;
	t_u8				mouse_warp;
	t_u32a				scene_redraw;
	t_u32a				reload;
	char				**rt_argv;
	int					rt_argc;
	t_arena_checkpoint	rewind_render;
	t_RTViewport		vp;
	t_RTPool			pool;
	t_map				loaded_textures;
}	t_RTContext;

/* cold, only lives in main */
typedef struct s_RTstate
{
	t_RTScene				scene;
	t_RTContext				ctx;
	t_u8					keys;
}	t_RTstate;

typedef enum e_taggedresult
{
	KO = 0,
	OK = 1
}	t_taggedresult;

void			rt_free_state(t_RTstate *state)\
					__attribute__((__nonnull__(1)));

t_taggedresult	rt_alloc_imagebuffer(t_RTContext *ctx)\
					__attribute__((__nonnull__(1)));

void			rt_putimg(t_RTContext *ctx)\
					__attribute__((__nonnull__(1)));

int				rt_render_hotloop(t_RTstate *state)\
					__attribute__((__nonnull__(1), hot));

t_taggedresult	rt_load_state(t_RTstate *state)\
					__attribute__((__nonnull__(1)));

void			*rt_threadrt(void *thread_arg)\
					__attribute__((__nonnull__(1)));

#endif
