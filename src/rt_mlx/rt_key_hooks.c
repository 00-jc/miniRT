/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_key_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:08:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/11 02:05:31 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define XK_LATIN1
#define XK_MISCELLANY
#include "rt_mlx/rt_mlx.h"

__attribute__((const, __always_inline__))
static inline t_3dcoords	rt_getmov(int key)
{
	static const t_3dcoords	movs[] = {
	[XK_w] = {0.0, 0.0, 1.0, 0.0},
	[XK_a] = {-1.0, 0.0, 0.0, 0.0},
	[XK_s] = {0.0, 0.0, -1.0, 0.0},
	[XK_d] = {1.0, 0.0, 0.0, 0.0},
	};

	return (movs[key]);
}

__attribute__((__nonnull__(2)))
int	rt_key_hook(int key, t_RTstate *restrict const state)
{
	if (key == XK_Delete)
		(rt_free_state(state), exit(EXIT_SUCCESS));
	else if ((key == XK_w) | (key == XK_a) | (key == XK_s) | (key == XK_d))
		state->scene.rt_camera.coords = ft_3dadd(state->scene.rt_camera.coords,
				rt_getmov(key));
	return (0);
}
