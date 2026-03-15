/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:02:11 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/14 21:56:07 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MLX_H
# define RT_MLX_H

# define RT_MOVEMENT 0.001
# define MOUSE_SENSITIVITY 8e-5
# include "rt_miniRT.h"
# include <X11/keysymdef.h>

extern double	sin(double a);
extern double	cos(double a);

int				rt_key_hook(t_RTstate *state)\
					__attribute__((__nonnull__(1)));

int				rt_key_press(int key, t_RTstate *restrict const state)\
					__attribute__((__nonnull__(2)));

int				rt_key_release(int key, t_RTstate *restrict const state)\
					__attribute__((__nonnull__(2)));

int				rt_handle_mouse_move(int x, int y, t_RTstate *state)\
					__attribute__((__nonnull__(3)));

int				rt_killprocess(t_RTstate *state)\
					__attribute__((noreturn, cold, __nonnull__(1)));
#endif
