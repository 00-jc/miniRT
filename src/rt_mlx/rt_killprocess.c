/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_killprocess.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:44:56 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/13 16:47:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_mlx/rt_mlx.h"

__attribute__((noreturn, cold, __nonnull__(1)))
int	rt_killprocess(t_RTstate *state)
{
	rt_free_state(state);
	exit(EXIT_SUCCESS);
}
