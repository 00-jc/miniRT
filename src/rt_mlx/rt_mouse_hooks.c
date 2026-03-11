/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mouse_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:23:04 by asoria            #+#    #+#             */
/*   Updated: 2026/03/11 18:37:30 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_mlx/rt_mlx.h"

int	rt_handle_mouse_move(int x, int y, t_RTstate *state)
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
	center_x = state->ctx.display_width / 2;
	center_y = state->ctx.display_height / 2;
	dx = x - center_x;
	dy = y - center_y;
	state->scene.rt_camera.axis.x = dy;// * MOUSE_SENSITIVITY;
	state->scene.rt_camera.axis.y = dx;// * MOUSE_SENSITIVITY;
	state->ctx.scene_is_dirty= 1;
	mlx_mouse_move(state->ctx.rt_mlx, state->ctx.rt_mlx_win, center_x, center_y);
	
	return (0);
}
