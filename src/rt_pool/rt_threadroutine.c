/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_threadroutine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:31:38 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/16 16:42:39 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_miniRT.h"
#include "rt_render/rt_render.h"

__attribute__((__nonnull__(1), hot))
void	*rt_threadrt(void *arg1)
{
	t_RTstate		*state;
	size_t			row;

	state = (t_RTstate *)arg1;
	while (1)
	{
		row = __atomic_fetch_add(&state->ctx.pool.current_tile,
				1, __ATOMIC_RELAXED);
		if (row >= state->ctx.display_height)
			return ((void *)1);
		rt_render_line(&state->ctx, &state->scene, row);
	}
	return ((void *)1);
}
