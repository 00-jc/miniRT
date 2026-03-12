/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mouse_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:23:04 by asoria            #+#    #+#             */
/*   Updated: 2026/03/12 11:52:26 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_mlx/rt_mlx.h"

__attribute__((__always_inline__, __nonnull__(1), hot))
inline void	rt_handle_axis_limits(t_RTstate *state)
{
	state->scene.rt_camera.axis.x += ((state->scene.rt_camera.axis.x > 1.0)
			* -2.0) + ((state->scene.rt_camera.axis.x < -1.0) * 2.0);
	state->scene.rt_camera.axis.y = (state->scene.rt_camera.axis.y > 1.0) * 1.0
		+ (state->scene.rt_camera.axis.y < -1.0) * -1.0
		+ (state->scene.rt_camera.axis.y >= -1.0
			&& state->scene.rt_camera.axis.y <= 1.0)
		* state->scene.rt_camera.axis.y;
}

__attribute__((__always_inline__, __nonnull__(3), hot))
inline int	rt_handle_mouse_move(int x, int y, t_RTstate *state)
{
	int	center_x;
	int	center_y;
	int	dx;
	int	dy;

	if (state->ctx.mouse_warp)
	{
		state->ctx.mouse_warp = 0;
		return (0);
	}
	center_x = state->ctx.display_width * 0.5;
	center_y = state->ctx.display_height * 0.5;
	dx = x - center_x;
	dy = y - center_y;
	state->scene.rt_camera.axis.x += dx * MOUSE_SENSITIVITY * 0.0055555555555;
	state->scene.rt_camera.axis.y += dy * MOUSE_SENSITIVITY * 0.0055555555555;
	rt_handle_axis_limits(state);
	mlx_mouse_move(state->ctx.rt_mlx, state->ctx.rt_mlx_win, center_x,
		center_y);
	state->ctx.mouse_warp = 1;
	state->ctx.scene_redraw = 1;
	return (0);
}
