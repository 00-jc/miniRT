/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:02:11 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/11 17:26:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MLX_H
# define RT_MLX_H

# define RT_MOVEMENT 0.01
# include "rt_miniRT.h"
# include <X11/keysymdef.h>

int	rt_key_hook(t_RTstate *state)\
	__attribute__((__nonnull__(1)));

int	rt_key_press(int key, t_RTstate *restrict const state)\
	__attribute__((__nonnull__(2)));

int	rt_key_release(int key, t_RTstate *restrict const state)\
	__attribute__((__nonnull__(2)));

#endif
