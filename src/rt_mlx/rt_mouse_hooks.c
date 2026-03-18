/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mouse_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:23:04 by asoria            #+#    #+#             */
/*   Updated: 2026/03/18 14:48:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_mlx/rt_mlx.h"
#include "rt_render/rt_render.h"

__attribute__((__always_inline__, __nonnull__(1), hot))
inline void	rt_handle_axis_limits(t_RTstate *state)
{
	t_RTCamera	*cam;

	cam = &state->scene.rt_camera;
	cam->yaw += (cam->yaw > RT_PI) * (-2.0 * RT_PI)
		+ (cam->yaw < -RT_PI) * (2.0 * RT_PI);
	cam->pitch = (cam->pitch > 1.5707) * 1.5707
		+ (cam->pitch < -1.5707) * -1.5707
		+ (cam->pitch >= -1.5707 && cam->pitch <= 1.5707) * cam->pitch;
	cam->axis.x = __builtin_cos(cam->pitch) * __builtin_sin(cam->yaw);
	cam->axis.y = __builtin_sin(cam->pitch);
	cam->axis.z = __builtin_cos(cam->pitch) * __builtin_cos(cam->yaw);
}

__attribute__((__always_inline__, __nonnull__(3), hot))
inline int	rt_handle_mouse_move(int x, int y, t_RTstate *state)
{
	double			center_x;
	double			center_y;
	double			dx;
	double			dy;

	if (state->ctx.mouse_warp)
	{
		state->ctx.mouse_warp = 0;
		return (0);
	}
	center_x = (double)state->ctx.display_width * 0.5;
	center_y = (double)state->ctx.display_height * 0.5;
	dx = x - center_x;
	dy = y - center_y;
	state->scene.rt_camera.yaw -= dx * MOUSE_SENSITIVITY;
	state->scene.rt_camera.pitch -= dy * MOUSE_SENSITIVITY;
	rt_handle_axis_limits(state);
	mlx_mouse_move(state->ctx.rt_mlx, state->ctx.rt_mlx_win, (int)center_x,
		(int)center_y);
	state->ctx.mouse_warp = 1;
	state->ctx.scene_redraw = 1;
	return (0);
}
