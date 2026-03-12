/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_hotloop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:20:46 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/12 03:22:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hint.h"
#include "rt_miniRT.h"
#include "rt_mlx/rt_mlx.h"

__attribute__((__nonnull__(1), hot))
int	rt_render_hotloop(t_RTstate *state)
{
	if (rt_reload(state) == KO)
		(rt_free_state(state), exit(EXIT_FAILURE));
	if (state->ctx.scene_redraw)
	{
		rt_putimg(&state->ctx);
	}
	return (0);
}
