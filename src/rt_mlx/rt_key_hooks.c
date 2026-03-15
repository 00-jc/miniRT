/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_key_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:08:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/15 18:46:58 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define XK_LATIN1
#define XK_MISCELLANY
#include "rt_mlx/rt_mlx.h"
#include "private/ft_p_math.h"

__attribute__((pure, __always_inline__, hot))
static inline t_u8	rt_key_to_bit(int key)
{
	static const t_u8	bits[] = {
	[XK_w] = KEY_W,
	[XK_a] = KEY_A,
	[XK_s] = KEY_S,
	[XK_d] = KEY_D,
	};

	if ((key < 0) | ((size_t)key >= sizeof(bits) / sizeof(*bits)))
		return (0);
	return (bits[key]);
}

__attribute__((__nonnull__(2), hot))
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

__attribute__((__nonnull__(2), hot))
int	rt_key_release(int key, t_RTstate *restrict const state)
{
	state->keys &= ~rt_key_to_bit(key);
	return (0);
}

__attribute__((__nonnull__(1), hot))
int	rt_key_hook(t_RTstate *restrict const state)
{
	t_v4da				final;
	t_v4da				fw;
	t_v4da				right;
	t_3dcoords			tmp;

	tmp = state->scene.rt_camera.axis;
	tmp = (t_3dcoords){tmp.x, 0, tmp.z, 0};
	tmp = ft_3dunit(tmp);
	fw = *(const t_v4da *)&tmp * RT_MOVEMENT;
	tmp = ft_3dunit(ft_3dcross(state->scene.rt_camera.axis,
				(t_3dcoords){0, 1, 0, 0}));
	right = *(const t_v4da *) & tmp * RT_MOVEMENT;
	final = (*(const t_v4da * restrict
				const) & state->scene.rt_camera.coords)
		+ (((state->keys & KEY_W) != 0) * fw)
		+ (((state->keys & KEY_A) != 0) * -right)
		+ (((state->keys & KEY_S) != 0) * -fw)
		+ (((state->keys & KEY_D) != 0) * right);
	state->scene.rt_camera.coords = *(const t_3dcoords * restrict
			const) & final;
	return (0);
}

/*
__attribute__((__nonnull__(1), hot))
int	rt_key_hook(t_RTstate *restrict const state)
{
	if (state->keys & KEY_W)
		state->scene.rt_camera.coords = ft_3dadd(state->scene.rt_camera.coords,
				(t_3dcoords){0.0, 0.0, RT_MOVEMENT, 0.0});
	if (state->keys & KEY_A)
		state->scene.rt_camera.coords = ft_3dadd(state->scene.rt_camera.coords,
				(t_3dcoords){-RT_MOVEMENT, 0.0, 0.0, 0.0});
	if (state->keys & KEY_S)
		state->scene.rt_camera.coords = ft_3dadd(state->scene.rt_camera.coords,
				(t_3dcoords){0.0, 0.0, -RT_MOVEMENT, 0.0});
	if (state->keys & KEY_D)
		state->scene.rt_camera.coords = ft_3dadd(state->scene.rt_camera.coords,
				(t_3dcoords){RT_MOVEMENT, 0.0, 0.0, 0.0});
	return (0);
}
*/
