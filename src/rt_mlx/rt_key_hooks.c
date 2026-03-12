/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_key_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:08:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/12 11:26:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define XK_LATIN1
#define XK_MISCELLANY
#include "rt_mlx/rt_mlx.h"

__attribute__((pure, __always_inline__))
static inline t_u8	rt_key_to_bit(int key)
{
	static const t_u8	bits[] = {
	[XK_w] = KEY_W,
	[XK_a] = KEY_A,
	[XK_s] = KEY_S,
	[XK_d] = KEY_D,
	};

	if (key < 0 | (size_t)key >= sizeof(bits) / sizeof(*bits))
		return (0);
	return (bits[key]);
}

__attribute__((__nonnull__(2)))
int	rt_key_press(int key, t_RTstate *restrict const state)
{
	state->ctx.scene_redraw = 1;
	if (key == XK_Escape)
		(rt_free_state(state), exit(EXIT_SUCCESS));
	if (key == XK_r)
		state->ctx.reload = 1;
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
				(t_3dcoords){0.0, 0.0, RT_MOVEMENT, 0.0});
	else if (state->keys & KEY_A)
		state->scene.rt_camera.coords = ft_3dadd(state->scene.rt_camera.coords,
				(t_3dcoords){-RT_MOVEMENT, 0.0, 0.0, 0.0});
	else if (state->keys & KEY_S)
		state->scene.rt_camera.coords = ft_3dadd(state->scene.rt_camera.coords,
				(t_3dcoords){0.0, 0.0, -RT_MOVEMENT, 0.0});
	else if (state->keys & KEY_D)
		state->scene.rt_camera.coords = ft_3dadd(state->scene.rt_camera.coords,
				(t_3dcoords){RT_MOVEMENT, 0.0, 0.0, 0.0});
	return (0);
}
