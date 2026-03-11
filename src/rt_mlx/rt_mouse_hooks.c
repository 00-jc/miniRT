/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mouse_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:23:04 by asoria            #+#    #+#             */
/*   Updated: 2026/03/11 17:58:27 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_mlx/rt_mlx.h"

inline int	rt_handle_mouse_move(int x, int y, t_RTstate *state)
{
	t_u8	center_x;
	t_u8	center_y;
	t_u8	dx;
	t_u8	dy;

	center_x = state->ctx.display_width / 2;
	center_y = state->ctx.display_height / 2;
	if (x == center_x && y == center_y)
		return (0);
	dx = x - center_x;
	dy = y - center_y;
	state->scene.rt_camera.axis.x = dy * MOUSE_SENSITIVITY;
	state->scene.rt_camera.axis.x = dx * MOUSE_SENSITIVITY;
	state->ctx.scene_is_dirty= 1;
	mlx_mouse_move(state->ctx.rt_mlx, state->ctx.rt_mlx_win, center_x, center_y);
	
	return (0);
}
