/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:02:11 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/11 13:29:46 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MLX_H
# define RT_MLX_H

# include "rt_miniRT.h"
# include <X11/keysymdef.h>

int	rt_key_hook(t_RTstate *state)\
	__attribute__((__nonnull__(1)));

int	rt_key_press(int key, t_RTstate *restrict const state)\
	__attribute__((__nonnull__(2)));

int	rt_key_release(int key, t_RTstate *restrict const state)\
	__attribute__((__nonnull__(2)));

#endif
