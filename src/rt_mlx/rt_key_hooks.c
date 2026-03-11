/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_key_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:08:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/11 13:55:12 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define XK_LATIN1
#define XK_MISCELLANY
#include "rt_mlx/rt_mlx.h"

__attribute__((__always_inline__))
inline t_u8	rt_key_to_bit(int key)
{
	static const t_u8	bits[256] = {
	[XK_w] = KEY_W,
	[XK_a] = KEY_A,
	[XK_s] = KEY_S,
	[XK_d] = KEY_D,
	};

	return (bits[key & 0xFF]);
}

__attribute__((__nonnull__(2)))
int	rt_key_press(int key, t_RTstate *restrict const state)
{
	if (key == XK_Escape)
		(rt_free_state(state), exit(EXIT_SUCCESS));
	state->keys |= rt_key_to_bit(key);
	return (0);
}

__attribute__((__nonnull__(2)))
int	rt_key_release(int key, t_RTstate *restrict const state)
{
	state->keys &= ~rt_key_to_bit(key);
	return (0);
}

__attribute__((__nonnull__(1)))
int	rt_key_hook(t_RTstate *restrict const state)
{
	if (state->keys & KEY_W)
		state->scene.rt_camera.coords = ft_3dadd(state->scene.rt_camera.coords,
				(t_3dcoords){0.0, 0.0, 1.0, 0.0});
	if (state->keys & KEY_A)
		state->scene.rt_camera.coords = ft_3dadd(state->scene.rt_camera.coords,
				(t_3dcoords){-1.0, 0.0, 0.0, 0.0});
	if (state->keys & KEY_S)
		state->scene.rt_camera.coords = ft_3dadd(state->scene.rt_camera.coords,
				(t_3dcoords){0.0, 0.0, -1.0, 0.0});
	if (state->keys & KEY_D)
		state->scene.rt_camera.coords = ft_3dadd(state->scene.rt_camera.coords,
				(t_3dcoords){1.0, 0.0, 0.0, 0.0});
	return (0);
}
